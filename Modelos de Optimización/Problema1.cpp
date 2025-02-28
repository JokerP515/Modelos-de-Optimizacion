#include <cstdlib>
#include <memory>

#include "ortools/base/logging.h"
#include "ortools/linear_solver/linear_solver.h"

namespace operations_research {
    void recursosServidor(){
        // Create the linear solver with the GLOP backend.
        std::unique_ptr<MPSolver> solver(MPSolver::CreateSolver("GLOP"));
        if (!solver) {
            LOG(WARNING) << "No se pudo inicializar el solver GLOP";
            return;
        }

        // Variables para representar la cantidad de tareas hechas por cada servidor
		// Contiene las restricciones de NO negatividad, TA <= 80 y TB <= 60
		MPVariable* const TA = solver->MakeNumVar(0.0, 80, "Tareas Servidor A");
		MPVariable* const TB = solver->MakeNumVar(0.0, 60, "Tareas Servidor B");

		// Restricción lineal de la cantidad total de tareas que se deben cumplir
		// TA + TB = 100
		MPConstraint* const totalTareas = solver->MakeRowConstraint(100, 100, "Total de tareas");
		totalTareas->SetCoefficient(TA, 1);
		totalTareas->SetCoefficient(TB, 1);

		// Función objetivo: Minimizar el coste total del procesamiento de los servidores
		// Zmin = 5 * TA + 3 * TB
		MPObjective* const objective = solver->MutableObjective();
		objective->SetCoefficient(TA, 5);
		objective->SetCoefficient(TB, 3);
		objective->SetMinimization();

		// Aplicando el solver GLOP para resolver el problema
        LOG(INFO) << "Solving with " << solver->SolverVersion();
        const MPSolver::ResultStatus result_status = solver->Solve();

        // Check that the problem has an optimal solution.
        LOG(INFO) << "Status: " << result_status;
        if (result_status != MPSolver::OPTIMAL) {
            LOG(INFO) << "Este problema no tiene una sol optima";
            if (result_status == MPSolver::FEASIBLE) {
                LOG(INFO) << "Se acaba de encontrar una solucion factible";
            }
            else {
                LOG(WARNING) << "Hubo un problema, Solver no pudo resolverlo";
                return;
            }
        }

        LOG(INFO) << "Solucion encontrada:";
        LOG(INFO) << "Valor min encontrado = " << objective->Value();
        LOG(INFO) << "Valor de TA = " << TA->solution_value();
        LOG(INFO) << "Valor de TB = " << TB->solution_value();

        LOG(INFO) << "Costo de la operacion realizada:";
        LOG(INFO) << "Problema resuelto en: " << solver->wall_time() << " milliseg";
        LOG(INFO) << "Problema resuelto en: " << solver->iterations() << " iteracion/es";

    }
}  // namespace operations_research