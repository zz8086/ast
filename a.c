#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "json_c.c"

typedef struct {
    char name[50];
} decl;

int main(void)
{
    long file_size;
    char *str;
    int count = 0;

    FILE *fp = fopen("ast.json", "r");

    if (fp == NULL) 
    {
        printf("파일을 열지 못했습니다.\n");
        return 1;
    }
    
    fseek(fp, 0, SEEK_END);
    file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    str = (char*)malloc(sizeof(char) * file_size);
    fread(str, 1, file_size, fp);

    json_value json = json_create(str);
    json_value ext_obj = json_get(json, "ext");

    int ext_len = json_len(ext_obj);
    decl *name_array = (decl *)malloc(sizeof(decl) * ext_len);

    for(int i = 0; i < ext_len; i++)
    {
            json_value ext_obj_array = json_get(ext_obj, i);
            json_value decl_obj = json_get(ext_obj_array, "decl");
            json_type decl_type = json_get_type(json_get(ext_obj_array, "decl"));
            if(decl_type == JSON_UNDEFINED) {
                continue;
            }
            else {
                    json_value decl_type_obj = json_get(decl_obj, "type"); 
                    json_value decl_type_type_obj = json_get(decl_type_obj, "type"); 
                    json_value decl_type_type_type_obj = json_get(decl_type_type_obj, "type"); 
                    json_value decl_type_type_names_obj = json_get(decl_type_type_type_obj, "names", 0); 
                    json_type decl_type_type_names_type = json_get_type(json_get(decl_type_type_type_obj, "names", 0));
                    if(decl_type_type_names_type == JSON_UNDEFINED) {
                        json_value decl_type_type_type_type_obj = json_get(decl_type_type_type_obj, "type");
                        json_value decl_type_type_type_type_names_obj = json_get(decl_type_type_type_type_obj, "names", 0);
                    }
                    char *name = json_get_string(decl_obj, "name");
                    strcpy(name_array[i].name, name);
                    printf("-----------------------------\n");
                    printf("함수 이름 : %s ", name); printf("리턴 타입 : ");
                    json_print(decl_type_type_names_obj); putchar('\n');
                    if(json_is_null(json_get(decl_type_obj, "args"))) printf(" 파라미터 타입과 변수명이 없습니다. \n");
                    else 
                    {
                        json_value decl_type_args_obj = json_get(decl_type_obj, "args");
                        json_value decl_type_args_params_obj = json_get(decl_type_args_obj, "params");
                        int params_len = json_len(decl_type_args_params_obj);
                        for(int j = 0; j < params_len; j++)
                        {
                            json_value decl_type_args_params_array = json_get(decl_type_args_params_obj, j);
                            json_value decl_type_args_params_type_obj = json_get(decl_type_args_params_array, "type");
                            if(1 == j)
                            {
                                json_value decl_type_args_params_type_declname_obj = json_get(decl_type_args_params_type_obj, "declname");
                                printf("변수 이름 : ");
                                json_print(decl_type_args_params_type_declname_obj);
                            }
                            json_value decl_type_args_params_type_type_obj = json_get(decl_type_args_params_type_obj, "type");
                            if(1 == j)
                            {
                                json_value decl_type_args_params_type_type_names_obj = json_get(decl_type_args_params_type_type_obj, "names", 0);
                                printf(" 파라미터 타입 : ");
                                json_print(decl_type_args_params_type_type_names_obj); putchar('\n');
                            }
                            json_value decl_type_args_params_type_type_declname_obj = json_get(decl_type_args_params_type_type_obj, "declname");
                            json_value decl_type_args_params_type_type_type_obj = json_get(decl_type_args_params_type_type_obj, "type");
                            json_value decl_type_args_params_type_type_type_names_obj = json_get(decl_type_args_params_type_type_type_obj, "names", 0);
                            printf("변수 이름 : ");
                            json_print(decl_type_args_params_type_type_declname_obj); printf(" 파라미터 타입 : ");
                            json_print(decl_type_args_params_type_type_type_names_obj); putchar('\n');
                        }

                    }
                    count++;
                    }   
    }
    printf("-----------------------------\n");
    printf("총 함수 갯수 : %d \n", count);

    free(str);
    fclose(fp);

    return 0;
}
