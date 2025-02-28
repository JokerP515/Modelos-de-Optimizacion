#include "absl/flags/flag.h"
#include "ortools/base/init_google.h"
#include "ortools/init/init.h"

#include "funciones.h"


int main(int argc, char* argv[]) {
    InitGoogle(argv[0], &argc, &argv, true);
    absl::SetFlag(&FLAGS_stderrthreshold, 0);
    //operations_research::UtilidadPinturas();
	operations_research::recursosServidor();
    return EXIT_SUCCESS;
}
