#include <cstdlib>
#include <memory>

#include "ortools/base/logging.h"
#include "ortools/linear_solver/linear_solver.h"

namespace operations_research {
	void tareasApp(){
        // Create the linear solver with the GLOP backend.
        std::unique_ptr<MPSolver> solver(MPSolver::CreateSolver("GLOP"));
        if (!solver) {
            LOG(WARNING) << "No se pudo inicializar el solver GLOP";
            return;
        }

		// Necesario para limites de variables y restricciones
		const double infinity = solver->infinity();

		// Variables para representar el número de tareas realizadas por semana en la app
		// TW = Tareas realizadas por semana en la app web
		// TM = Tareas realizadas por semana en la app móvil
		// Contiene las restricciones de NO negatividad, TW >= 0 y TM >= 0
		MPVariable* const TW = solver->MakeNumVar(0.0, infinity, "Tareas App Web");
		MPVariable* const TM = solver->MakeNumVar(0.0, infinity, "Tareas App Movil");

		// Restricción para el limite de horas de desarrollo por semana
		// 6 * TW + 4 * TM <= 40
		MPConstraint* const horasDesarrollo = solver->MakeRowConstraint(-infinity, 40.0, "Horas de desarrollo por semana");
		horasDesarrollo->SetCoefficient(TW, 6);
		horasDesarrollo->SetCoefficient(TM, 4);

		// Restricción: Al menos el doble de horas trabajadas en la app web comparado a la app móvil
		// 6*TW >= 2*(4*TM) => 6*TW - 8*TM >= 0
		MPConstraint* const dobleHoras = solver->MakeRowConstraint(0.0, infinity, "Doble de horas trabajadas en la app web");
		dobleHoras->SetCoefficient(TW, 6);
		dobleHoras->SetCoefficient(TM, -8);

		// Función objetivo: Maximizar el número de tareas realizadas por semana
		// Zmax = TW + TM
		MPObjective* const objective = solver->MutableObjective();
		objective->SetCoefficient(TW, 1);
		objective->SetCoefficient(TM, 1);
		objective->SetMaximization();



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
		LOG(INFO) << "Valor Zmax encontrado = " << objective->Value();
		LOG(INFO) << "Valor de TW = " << TW->solution_value();
		LOG(INFO) << "Valor de TM = " << TM->solution_value();
		LOG(INFO) << "Cantidad de horas de TW: " << 6 * TW->solution_value();
		LOG(INFO) << "Cantidad de horas de TM: " << 4 * TM->solution_value();

		LOG(INFO) << "Costo de la operacion realizada:";
		LOG(INFO) << "Problema resuelto en: " << solver->wall_time() << " milliseg";
		LOG(INFO) << "Problema resuelto en: " << solver->iterations() << " iteracion/es";

	}
}