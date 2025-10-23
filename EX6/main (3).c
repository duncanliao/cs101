#include <stdio.h>

typedef struct employee {
    int id;
    int age;
    int salary;
    char name[50];
} employee_t;

void emp_info(employee_t emp) {
    printf("ID: %d, Age: %d, Salary: %d, Name: %s\n", emp.id, emp.age, emp.salary, emp.name);
}

int emp_average_age(employee_t emp[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += emp[i].age;
    }
    return (n > 0) ? sum / n : 0;
}

void emp_writefile(employee_t emp[], int n) {
    FILE *fp = fopen("employee.bin", "wb");
    if (fp != NULL) {
        fwrite(emp, sizeof(employee_t), n, fp);
        fclose(fp);
    }
}

void emp_readfile(employee_t emp[], int n) {
    FILE *fp = fopen("employee.bin", "rb");
    if (fp != NULL) {
        fread(emp, sizeof(employee_t), n, fp);
        fclose(fp);
    }
}

int main() {
    employee_t emp[3];

    // 初始化示例數據
    emp[0].id = 1;
    emp[0].age = 20;
    emp[0].salary = 30000;
    snprintf(emp[0].name, 50, "Tom");

    emp[1].id = 2;
    emp[1].age = 25;
    emp[1].salary = 35000;
    snprintf(emp[1].name, 50, "Jerry");

    emp[2].id = 3;
    emp[2].age = 30;
    emp[2].salary = 40000;
    snprintf(emp[2].name, 50, "Alice");

    // 顯示員工資訊
    for (int i = 0; i < 3; i++) {
        emp_info(emp[i]);
    }

    // 計算並顯示平均年齡
    int avg_age = emp_average_age(emp, 3);
    printf("Average Age: %d\n", avg_age);

    // 寫入檔案
    emp_writefile(emp, 3);

    return 0;
}