#include <stdio.h>//��������� ������� 
#include <stdlib.h>//system ������� 
#include <windows.h>//windows func ������� 
#include <string.h>//���ڿ� �Լ� ������� 
#include <stdbool.h>//Ʈ��, ���� ��� 
#include <conio.h>//getch, kbhit

void gotoxy(int, int);

#define MAX 25//�ִ� 
#define cls system("cls")//ȭ��Ŭ���� 

typedef struct _student{//�л� ����ü 
	int number;//�й� 
	char name[MAX];//�̸� 
	int kor, eng, any;//���� 
	int sum;//���� 
	double avg;//��� 
	int rank;//���(i��ſ� stu[i].rank++;�� �ᵵ ��) 
	char r;//���(a, b, c, d, e, f) 
} student;

void gotoxy(int x, int y) {//�ش� x, y ������ ��ǥ�̵� 
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int comp1(const void *a, const void *b) {//��������� 
	student *num1 = (student *)a;
	student *num2 = (student *)b;
	
	if(num1->avg > num2->avg) {//��������� ���� ����� ������ 
		return -1;
	} 
	
	if(num1->avg < num2->avg) {
		return 1;
	}
	
	return 0;
}

int comp2(const void *a, const void *b) {//��ȣ�� 
	student *num1 = (student *)a;
	student *num2 = (student *)b;
	
	if(num1->number < num2->number) {//����(1�� ù��° �����ϹǷ� ������������ ���� ��µ�) 
		return -1;
	} 
	
	if(num1->number > num2->number) {
		return 1;
	}
	
	return 0;
}

int checkFerror(FILE *fp) {//������ �����ϴ� ��(exist) Ȯ�� 
	if(fp == NULL) return 1;//����(if) �������� ������(it isn't exist) 
	else return 0;//����(if) �����ϸ�(it is exist) 
}

void nocursor() {//Ŀ�� ����� 
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };//�ʱ�ȭ 
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;//����� 
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);//������� ���� 
}

int main() {
	FILE *fin = fopen("rank.txt", "r"), *fout1 = fopen("NumberRank.db", "w"), *fout2 = fopen("WriteRank.db", "w"), *fout3 = fopen("Search.db", "w");
	int n, i, choose;//n�� �ݺ��ϱ����� i, �޴������� ���� choose 
	student stu[MAX];//�ִ� 25���� ��ȣ�� �� 
	char key[MAX];//25
	char any;//
	int is_find_on = 0;//ã���� ��Ÿ���� �÷��� 
	char path[128];
	
	nocursor();//Ŀ������� 
	system("title STUDENT_v1.1");//Ÿ��Ʋ ���� ���� 
	
	if(checkFerror(fin) == 0) {//rank.txt�� �� ���α׷��� �ִ� ��ο� �����Ѵٸ� 
			fscanf(fin, "%d", &n);//n�� �Է¹��� 
			for(i = 0; i < n; i++) {//n���� �л��� ������� �̸��� �Է¹��� 
				fscanf(fin, "%d %s %d %d %d", &stu[i].number, stu[i].name, &stu[i].kor, &stu[i].eng, &stu[i].any);
				stu[i].sum = stu[i].kor + stu[i].eng + stu[i].any;//��հ� ������ ���� 
				stu[i].avg = stu[i].sum / 3.0;
			}
			//�޴��׸��� 
			system("cls");
			gotoxy(24, 10);
			printf("1.�������(��ȣ��)");
			gotoxy(24, 11);
			printf("2.������ ���(����)");
			gotoxy(24, 12);
			printf("3.�˻�(�̸� : ȫ�浿)");
			gotoxy(24, 13);
			printf("4.����\n");
			scanf("%d", &choose);//�޴����ð� ���� 
			if(choose == 1) {//�й������ 
				qsort(stu, n, sizeof(student), comp2);//�й������� ���� 
				cls;//ȭ������� 
				printf("ó����...");
				Sleep(1500);
				cls;
				printf("%5s %5s %5s %5s %5s %5s %5s %5s %5s\n", "��ȣ", "�̸�", "����", "����", "����", "����", "���", "���", "���");
				fprintf(fout1, "%5s %5s %5s %5s %5s %5s %5s %5s %5s\n", "��ȣ", "�̸�", "����", "����", "����", "����", "���", "���", "���");
				for(i = 0; i < n; i++) {//����� �ű�鼭 ��� 
					if(stu[i].avg >= 10.0 && stu[i].avg <= 30.0) stu[i].r = 'F';
					if(stu[i].avg >= 30.0 && stu[i].avg <= 45.0) stu[i].r = 'E';
					if(stu[i].avg >= 45.0 && stu[i].avg <= 55.0) stu[i].r = 'D';
					if(stu[i].avg >= 55.0 && stu[i].avg <= 70.0) stu[i].r = 'C';
					if(stu[i].avg >= 70.0 && stu[i].avg <= 85.0) stu[i].r = 'B';
					if(stu[i].avg >= 85.0 && stu[i].avg <= 100.0) stu[i].r = 'A';
					printf(" %d    %s   %d   %d   %d   %d   %.1lf   %c   %d\n", stu[i].number, stu[i].name, stu[i].kor, stu[i].eng, stu[i].any, stu[i].sum, stu[i].avg, stu[i].r, i+1);
					fprintf(fout1, " %d    %s   %d   %d   %d   %d   %.1lf   %c   %d\n", stu[i].number, stu[i].name, stu[i].kor, stu[i].eng, stu[i].any, stu[i].sum, stu[i].avg, stu[i].r, i+1);
				}
				printf("����� �������� ���ư��ϴ�.");//�ƹ�Ű�� ������ �������� ���ư� 
				system("pause");
				cls;
				main();//�ٽ� �������� ���ư� 
			} else if(choose == 2) {
				qsort(stu, n, sizeof(student), comp1);//��ռ����� ���� 
				cls;
				printf("ó����...");
				Sleep(1500);
				cls;
				printf("%5s %5s %5s %5s %5s %5s %5s %5s %5s\n", "��ȣ", "�̸�", "����", "����", "����", "����", "���", "���", "���");
				for(i = 0; i < n; i++) {
					if(stu[i].avg >= 10.0 && stu[i].avg <= 30.0) stu[i].r = 'F';
					if(stu[i].avg >= 30.0 && stu[i].avg <= 45.0) stu[i].r = 'E';
					if(stu[i].avg >= 45.0 && stu[i].avg <= 55.0) stu[i].r = 'D';
					if(stu[i].avg >= 55.0 && stu[i].avg <= 70.0) stu[i].r = 'C';
					if(stu[i].avg >= 70.0 && stu[i].avg <= 85.0) stu[i].r = 'B';
					if(stu[i].avg >= 85.0 && stu[i].avg <= 100.0) stu[i].r = 'A';
					printf(" %d    %s   %d   %d   %d   %d   %.1lf   %c   %d\n", stu[i].number, stu[i].name, stu[i].kor, stu[i].eng, stu[i].any, stu[i].sum, stu[i].avg, stu[i].r, i+1);
					fprintf(fout2, " %d    %s   %d   %d   %d   %.1lf   %c   %d\n", stu[i].number, stu[i].name, stu[i].kor, stu[i].eng, stu[i].any, stu[i].sum, stu[i].avg, stu[i].r, i+1);
				}
				printf("�ƹ�Ű�� ������ �������� ���ư��ϴ�.");
				system("pause");
				system("cls");
				main();
			} else if(choose == 3) {
				printf("�˻��� ����� �̸� �Է� : ");
				scanf("%s", key);//����� �Է¹��� 
				qsort(stu, n, sizeof(student), comp1);//���� 
				for(i = 0; i < n; i++) {
					if(stu[i].avg >= 10.0 && stu[i].avg <= 30.0) stu[i].r = 'F';
					if(stu[i].avg >= 30.0 && stu[i].avg <= 45.0) stu[i].r = 'E';
					if(stu[i].avg >= 45.0 && stu[i].avg <= 55.0) stu[i].r = 'D';
					if(stu[i].avg >= 55.0 && stu[i].avg <= 70.0) stu[i].r = 'C';
					if(stu[i].avg >= 70.0 && stu[i].avg <= 85.0) stu[i].r = 'B';
					if(stu[i].avg >= 85.0 && stu[i].avg <= 100.0) stu[i].r = 'A';
					if(strcmp(stu[i].name, key) == 0) {//key�� stu[i].name�� ��ġ�Ѵٸ� 
						printf("�ش����� ã�ҽ��ϴ�.\n");
						system("pause");
						system("cls");
						printf("%5s %5s %5s %5s %5s %5s %5s %5s %5s\n", "��ȣ", "�̸�", "����", "����", "����", "����", "���", "���", "���");
						printf(" %d    %s   %d   %d   %d   %d   %.1lf   %c   %d\n", stu[i].number, stu[i].name, stu[i].kor, stu[i].eng, stu[i].any, stu[i].sum, stu[i].avg, stu[i].r, i+1);
						fprintf(fout3, "������ �˻����...: %s�� ����", stu[i].name);
						is_find_on = 1;//ã���÷��׸� Ŵ 
					}
				}
				if(is_find_on == 0) {
					printf("ã�� ���Ͽ����ϴ�..");
					system("pause");
					system("cls");
					main();
				} else {
					system("pause");
					system("cls");
					//is_find_on �ʱ�ȭ�� �� �ʿ䰡 ����. ���ο��� ó���κп� �ʱ�ȭ�ϴϱ� 
					main();
				}
			} else if(choose == 4) {
				exit(1);//�ٷ����� 
			} else if(choose == 1234){
				printf("�̽��Ϳ��״� �������� ��������..����\n");
				system("pause");
				system("cls");
				
				gotoxy(12, 24);
				printf("< Dev Info >");
				gotoxy(12, 25);
				printf("< Dev : Rapiz(KISHA) >");
				gotoxy(12, 26);
				printf("< https://blog.naver.com/imra09 >");
				gotoxy(12, 27);
				printf("< Please Be my Friends! >");
				gotoxy(12, 30);
				printf("< Press Any Key To Continue >");
				_getch();
				main();
			} else {
				printf("error\n");
				system("pause");
				system("cls");
				return 0;
			}
		}  else {
			printf("������ �������� �ʽ��ϴ�. rank.txt������ �ش����α׷��� ��ο� ���� n���� �״����ٺ��� �й�, �̸�, ��, ��, �� ������ ���� �Է����ֽñ� �ٶ��ϴ�.\n");
			system("pause");
			system("cls");
			printf("Ȥ�� �𸣴ϱ� ��θ� �Է����ּ��� : ");
			scanf("%s", path);
			fin = fopen(path, "r");
			if(checkFerror(fin) == 0) {
				printf("�� ������ �� ���α׷��� ��ο� �μ���.\n");
				system("pause");
				system("cls");
				main();
			} else {
				system("pause");
				system("cls");
				printf("��ΰ� �����ϴ�.\n");
				system("pause");
				system("cls");
				exit(1);
			}
		}
	
	return 0;
}
