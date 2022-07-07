#include <stdio.h>
#include <omp.h>

int main() {

    printf("\nRunning application on Host: \n");
    printf("  Number of devices: %i\n", omp_get_num_devices());
    printf("  Is host device: %i\n", omp_is_initial_device());
    printf("  Host device id: %i\n", omp_get_initial_device());
    printf("  Default device id: %i\n", omp_get_default_device());

    printf("\nStart offloading block: \n");
#pragma omp target teams num_teams(2)
#pragma omp parallel num_threads(4)
    {
#pragma omp single nowait
        {
            printf("  Number of teams per device: %i\n", omp_get_num_teams());
            printf("  Number of threads per team: %i\n", omp_get_num_threads());
            printf("  Is host device: %i\n", omp_is_initial_device());
        }
    }
}
