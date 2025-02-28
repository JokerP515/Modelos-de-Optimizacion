#include <iostream>

#include "absl/flags/flag.h"
#include "ortools/base/init_google.h"
#include "ortools/init/init.h"

#include "funciones.h"

int main(int argc, char* argv[]) {
	// Inicializar Google Logging
    InitGoogle(argv[0], &argc, &argv, true);
	// Inicializar Google Flags
    absl::SetFlag(&FLAGS_stderrthreshold, 0);
    
	std::cout << "Problema 1: Utilidad de pinturas" << std::endl;
    operations_research::utilidadPinturas();
	
    std::cout << std::endl;

	std::cout << "Problema 2: << Problema 2: Asignación de Recursos en un Servidor" << std::endl;
    operations_research::recursosServidor();

    return EXIT_SUCCESS;
}
