#pragma once
#define ROW 3 
#define COL 3 

void matrix_init(int a[ROW][COL]); 
void matrix_add(int a[ROW][COL], int b[ROW][COL], int c[ROW][COL]); 
void matrix_mult(int a[ROW][COL], int b[ROW][COL], int c[ROW][COL]); 
void matrix_trans(int a[ROW][COL], int b[ROW][COL]); 
void matrix_print(int a[ROW][COL]);

