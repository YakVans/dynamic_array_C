#include <stdio.h>
#include <stdlib.h>

#include "dynamic_array.h"
#include "manual_read.h"
#include "errors.h"


void int_x2(const void *src, void *dest) {
    *(int*)dest = *(int*)src * 2;
}
void int_plus1(const void *src, void *dest) {
    *(int*)dest = *(int*)src + 1;
}
void int_square(const void *src, void *dest) {
    *(int*)dest = *(int*)src * *(int*)src;
}

void double_x2(const void *src, void *dest) {
    *(double*)dest = *(double*)src * 2;
}
void double_plus1(const void *src, void *dest) {
    *(double*)dest = *(double*)src + 1;
}
void double_square(const void *src, void *dest) {
    *(double*)dest = *(double*)src * *(double*)src;
}

int int_gr_eq0(const void *element) {
    return *(int*)element >= 0;
}
int int_eq1(const void *element) {
    return *(int*)element == 1;
}
int int_less_minus3(const void *element) {
    return *(int*)element < -3;
}

int double_gr_eq0(const void *element) {
    return *(double*)element >= 0;
}
int double_eq1(const void *element) {
    return *(double*)element == 1;
}
int double_less_minus3(const void *element) {
    return *(double*)element < -3;
}

typedef void (*map_func_t)(const void *, void *);
typedef int (*where_func_t)(const void *);

map_func_t* create_int_map_functions() {
    map_func_t *funcs = malloc(3 * sizeof(map_func_t));
    funcs[0] = (map_func_t)int_x2;
    funcs[1] = (map_func_t)int_plus1;
    funcs[2] = (map_func_t)int_square;
    return funcs;
}
where_func_t* create_int_where_functions() {
    where_func_t *funcs = malloc(3 * sizeof(where_func_t));
    funcs[0] = (where_func_t)int_gr_eq0;
    funcs[1] = (where_func_t)int_eq1;
    funcs[2] = (where_func_t)int_less_minus3;
    return funcs;
}
map_func_t* create_double_map_functions() {
    map_func_t *funcs = malloc(3 * sizeof(map_func_t));
    funcs[0] = (map_func_t)double_x2;
    funcs[1] = (map_func_t)double_plus1;
    funcs[2] = (map_func_t)double_square;
    return funcs;
}
where_func_t* create_double_where_functions() {
    where_func_t *funcs = malloc(3 * sizeof(where_func_t));
    funcs[0] = (where_func_t)double_gr_eq0;
    funcs[1] = (where_func_t)double_eq1;
    funcs[2] = (where_func_t)double_less_minus3;
    return funcs;
}

DynamicArray *CreationUI(int my_type) {
    DynamicArray *arr = NULL;
    ErrorCode err;
    while (1) {
        err = SUCCESS;
        printf("\nArray: ");
        if (my_type == 1) {
            arr = ReadManyInt(&err);
        }
        else if (my_type == 2) {
            arr = ReadManyDouble(&err);
        }

        if (err != SUCCESS) {
            print_error(err);
            continue;
        }
        else {
            break;
        }
    }
    return arr;
}

DynamicArray *AssignUI(int *my_type) {
    ErrorCode err;
    printf("\nPossible types:\n");
    printf("1. int\n");
    printf("2. double\n");
    while (1) {
        err = SUCCESS;
        printf("\nChoice: ");
        *my_type = ReadOneInt(&err);

        if (err != SUCCESS) {
            print_error(err);
            continue;
        }

        if (*my_type < 1 || *my_type > 2) {
            printf("Numbers can be only 1 or 2\n");
        }
        else {
            break;
        }
    }
    return CreationUI(*my_type);
}

void MapUI(DynamicArray **arr, int my_type) {
    printf("\nPossible map:\n");
    printf("1. * 2\n");
    printf("2. + 1\n");
    printf("3. ^2\n");

    ErrorCode err;
    int map_choice;
    while (1) {
        err = SUCCESS;
        printf("\nMap choice: ");
        map_choice = ReadOneInt(&err);

        if (err != SUCCESS) {
            print_error(err);
            continue;
        }

        if (map_choice < 1 || map_choice > 3) {
            printf("Numbers can be only 1-3\n");
        }
        else {
            break;
        }
    }
    DAErrorPair arr_plus_err;
    if (my_type == 1) {
        map_func_t *int_map_func = create_int_map_functions();
        arr_plus_err = dynamic_array_map(*arr, int_map_func[map_choice - 1]);
        free(int_map_func);
    }
    else {
        map_func_t *double_map_func = create_double_map_functions();
        arr_plus_err = dynamic_array_map(*arr, double_map_func[map_choice - 1]);
        free(double_map_func);
    }

    if (arr_plus_err.errorCode != SUCCESS) {
        print_error(arr_plus_err.errorCode);
        return;
    }

    dynamic_array_free(*arr);
    *arr = arr_plus_err.result;
    dynamic_array_print(*arr);
}

void FilterUI(DynamicArray **arr, int my_type) {
    printf("\nPossible filter:\n");
    printf("1. >= 0\n");
    printf("2. == 1\n");
    printf("3. < -3\n");

    ErrorCode err;
    int filter_choice;
    while (1) {
        err = SUCCESS;
        printf("\nFilter choice: ");
        filter_choice = ReadOneInt(&err);

        if (err != SUCCESS) {
            print_error(err);
            continue;
        }

        if (filter_choice < 1 || filter_choice > 3) {
            printf("Numbers can be only 1-3\n");
        }
        else {
            break;
        }
    }
    DAErrorPair arr_plus_err;
    if (my_type == 1) {
        where_func_t *int_where_func = create_int_where_functions();
        arr_plus_err = dynamic_array_where(*arr, int_where_func[filter_choice - 1]);
        free(int_where_func);
    }
    else {
        where_func_t *double_where_func = create_double_where_functions();
        arr_plus_err = dynamic_array_where(*arr, double_where_func[filter_choice - 1]);
        free(double_where_func);
    }

    if (arr_plus_err.errorCode != SUCCESS) {
        print_error(arr_plus_err.errorCode);
        return;
    }
    
    dynamic_array_free(*arr);
    *arr = arr_plus_err.result;
    dynamic_array_print(*arr);
}

void SortUI(DynamicArray **arr) {
    ErrorCode err = dynamic_array_sort(*arr);

    if (err != SUCCESS) {
        print_error(err);
    }
    dynamic_array_print(*arr);
}

void ConcatUI(DynamicArray **arr, int my_type) {
    DynamicArray *new_arr = CreationUI(my_type);
    ErrorCode err = dynamic_array_concat(*arr, new_arr);
    if (err != SUCCESS) {
        print_error(err);
    }
    dynamic_array_free(new_arr);
    free(new_arr);
    dynamic_array_print(*arr);
}

void OperationsUI(DynamicArray **arr, int my_type) {
    ErrorCode err;
    while (1) {
        err = SUCCESS;
        printf("\nPossible operations:\n");
        printf("1. map\n");
        printf("2. filter\n");
        printf("3. sort\n");
        printf("4. concat with\n");
        printf("0. back to menu\n");
        int option;
        while (1) {
            err = SUCCESS;
            printf("\nOperation choice: ");
            option = ReadOneInt(&err);

            if (err != SUCCESS) {
                print_error(err);
                continue;
            }

            if (option < 0 || option > 4) {
                printf("Numbers can be only 0-4\n");
            }
            else {
                break;
            }
        }
        if (option == 0) {
            break;
        }
        else if (option == 1) {
            MapUI(arr, my_type);
        }
        else if (option == 2) {
            FilterUI(arr, my_type);
        }
        else if (option == 3) {
            SortUI(arr);
        }
        else if (option == 4) {
            ConcatUI(arr, my_type);
        }
    }
}

void MainMenuUI() {
    ErrorCode err;
    while (1) {
        printf("\n--- Main menu ---\n");
        printf("1. Create new\n");
        printf("0. Exit\n");
        
        int choice;
        while (1) {
            err = SUCCESS;
            printf("\nChoice: ");
            choice = ReadOneInt(&err);

            if (err != SUCCESS) {
                print_error(err);
                continue;
            }

            if (choice < 0 || choice > 1) {
                printf("Numbers can be only 0 or 1\n");
            }
            else {
                break;
            }
        }

        int my_type;
        if (choice == 0) {
            break;
        }
        else {
            DynamicArray *arr = AssignUI(&my_type);
            OperationsUI(&arr, my_type);
            dynamic_array_free(arr);
            free(arr);
        }
    }
}

int main() {
    MainMenuUI();
    return 0;
}