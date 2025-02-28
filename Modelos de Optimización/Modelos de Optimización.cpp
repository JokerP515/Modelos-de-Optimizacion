#include <iostream>

#include "absl/flags/flag.h"
#include "ortools/base/init_google.h"
#include "ortools/init/init.h"

#include "funciones.h"

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "");
	// Inicializar Google Logging
    InitGoogle(argv[0], &argc, &argv, true);
	// Inicializar Google Flags
    absl::SetFlag(&FLAGS_stderrthreshold, 0);
    
	std::cout << "Problema Clase 1: Utilidad de pinturas" << std::endl;
    operations_research::utilidadPinturas();
	
    std::cout << std::endl;

	std::cout << "Problema 1 Taller 4: Asignación de Recursos en un Servidor" << std::endl;
    operations_research::recursosServidor();

	std::cout << std::endl;

	std::cout << "Problema 2 Taller 4: Planificación de Mantenimiento de Software" << std::endl;
	operations_research::tareasApp();

    return EXIT_SUCCESS;
}
