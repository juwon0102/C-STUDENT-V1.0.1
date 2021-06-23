#include <stdio.h>//파일입출력 헤더파일 
#include <stdlib.h>//system 헤더파일 
#include <windows.h>//windows func 헤더파일 
#include <string.h>//문자열 함수 헤더파일 
#include <stdbool.h>//트루, 폴스 헤더 
#include <conio.h>//getch, kbhit

void gotoxy(int, int);

#define MAX 25//최댓값 
#define cls system("cls")//화면클리어 

typedef struct _student{//학생 구조체 
	int number;//학번 
	char name[MAX];//이름 
	int kor, eng, any;//점수 
	int sum;//총점 
	double avg;//평균 
	int rank;//등수(i대신에 stu[i].rank++;을 써도 됌) 
	char r;//등급(a, b, c, d, e, f) 
} student;

void gotoxy(int x, int y) {//해당 x, y 값으로 좌표이동 
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int comp1(const void *a, const void *b) {//평균점수순 
	student *num1 = (student *)a;
	student *num2 = (student *)b;
	
	if(num1->avg > num2->avg) {//평균점수에 따라 등급이 정해짐 
		return -1;
	} 
	
	if(num1->avg < num2->avg) {
		return 1;
	}
	
	return 0;
}

int comp2(const void *a, const void *b) {//번호순 
	student *num1 = (student *)a;
	student *num2 = (student *)b;
	
	if(num1->number < num2->number) {//순서(1이 첫번째 여야하므로 가장작은수가 먼저 출력됨) 
		return -1;
	} 
	
	if(num1->number > num2->number) {
		return 1;
	}
	
	return 0;
}

int checkFerror(FILE *fp) {//파일이 존재하는 지(exist) 확인 
	if(fp == NULL) return 1;//만약(if) 존재하지 않으면(it isn't exist) 
	else return 0;//만약(if) 존재하면(it is exist) 
}

void nocursor() {//커서 숨기기 
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };//초기화 
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;//숨기기 
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);//변경사항 적용 
}

int main() {
	FILE *fin = fopen("rank.txt", "r"), *fout1 = fopen("NumberRank.db", "w"), *fout2 = fopen("WriteRank.db", "w"), *fout3 = fopen("Search.db", "w");
	int n, i, choose;//n번 반복하기위해 i, 메뉴선택을 위해 choose 
	student stu[MAX];//최대 25명의 번호순 값 
	char key[MAX];//25
	char any;//
	int is_find_on = 0;//찾음을 나타내는 플래그 
	char path[128];
	
	nocursor();//커서숨기기 
	system("title STUDENT_v1.1");//타이틀 제목 변경 
	
	if(checkFerror(fin) == 0) {//rank.txt가 이 프로그램이 있는 경로에 존재한다면 
			fscanf(fin, "%d", &n);//n을 입력받음 
			for(i = 0; i < n; i++) {//n명의 학생의 점수들과 이름을 입력받음 
				fscanf(fin, "%d %s %d %d %d", &stu[i].number, stu[i].name, &stu[i].kor, &stu[i].eng, &stu[i].any);
				stu[i].sum = stu[i].kor + stu[i].eng + stu[i].any;//평균과 총점을 구함 
				stu[i].avg = stu[i].sum / 3.0;
			}
			//메뉴그리기 
			system("cls");
			gotoxy(24, 10);
			printf("1.성적출력(번호순)");
			gotoxy(24, 11);
			printf("2.석차순 출력(정렬)");
			gotoxy(24, 12);
			printf("3.검색(이름 : 홍길동)");
			gotoxy(24, 13);
			printf("4.종료\n");
			scanf("%d", &choose);//메뉴선택값 저장 
			if(choose == 1) {//학번순출력 
				qsort(stu, n, sizeof(student), comp2);//학번순으로 정렬 
				cls;//화면지우기 
				printf("처리중...");
				Sleep(1500);
				cls;
				printf("%5s %5s %5s %5s %5s %5s %5s %5s %5s\n", "번호", "이름", "국어", "영어", "수학", "총점", "평균", "등급", "등수");
				fprintf(fout1, "%5s %5s %5s %5s %5s %5s %5s %5s %5s\n", "번호", "이름", "국어", "영어", "수학", "총점", "평균", "등급", "등수");
				for(i = 0; i < n; i++) {//등급을 매기면서 출력 
					if(stu[i].avg >= 10.0 && stu[i].avg <= 30.0) stu[i].r = 'F';
					if(stu[i].avg >= 30.0 && stu[i].avg <= 45.0) stu[i].r = 'E';
					if(stu[i].avg >= 45.0 && stu[i].avg <= 55.0) stu[i].r = 'D';
					if(stu[i].avg >= 55.0 && stu[i].avg <= 70.0) stu[i].r = 'C';
					if(stu[i].avg >= 70.0 && stu[i].avg <= 85.0) stu[i].r = 'B';
					if(stu[i].avg >= 85.0 && stu[i].avg <= 100.0) stu[i].r = 'A';
					printf(" %d    %s   %d   %d   %d   %d   %.1lf   %c   %d\n", stu[i].number, stu[i].name, stu[i].kor, stu[i].eng, stu[i].any, stu[i].sum, stu[i].avg, stu[i].r, i+1);
					fprintf(fout1, " %d    %s   %d   %d   %d   %d   %.1lf   %c   %d\n", stu[i].number, stu[i].name, stu[i].kor, stu[i].eng, stu[i].any, stu[i].sum, stu[i].avg, stu[i].r, i+1);
				}
				printf("잠시후 메인으로 돌아갑니다.");//아무키나 누르면 메인으로 돌아감 
				system("pause");
				cls;
				main();//다시 메인으로 돌아감 
			} else if(choose == 2) {
				qsort(stu, n, sizeof(student), comp1);//평균순으로 정렬 
				cls;
				printf("처리중...");
				Sleep(1500);
				cls;
				printf("%5s %5s %5s %5s %5s %5s %5s %5s %5s\n", "번호", "이름", "국어", "영어", "수학", "총점", "평균", "등급", "등수");
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
				printf("아무키나 누르면 메인으로 돌아갑니다.");
				system("pause");
				system("cls");
				main();
			} else if(choose == 3) {
				printf("검색할 사람의 이름 입력 : ");
				scanf("%s", key);//사람을 입력받음 
				qsort(stu, n, sizeof(student), comp1);//정렬 
				for(i = 0; i < n; i++) {
					if(stu[i].avg >= 10.0 && stu[i].avg <= 30.0) stu[i].r = 'F';
					if(stu[i].avg >= 30.0 && stu[i].avg <= 45.0) stu[i].r = 'E';
					if(stu[i].avg >= 45.0 && stu[i].avg <= 55.0) stu[i].r = 'D';
					if(stu[i].avg >= 55.0 && stu[i].avg <= 70.0) stu[i].r = 'C';
					if(stu[i].avg >= 70.0 && stu[i].avg <= 85.0) stu[i].r = 'B';
					if(stu[i].avg >= 85.0 && stu[i].avg <= 100.0) stu[i].r = 'A';
					if(strcmp(stu[i].name, key) == 0) {//key와 stu[i].name이 일치한다면 
						printf("해당사람을 찾았습니다.\n");
						system("pause");
						system("cls");
						printf("%5s %5s %5s %5s %5s %5s %5s %5s %5s\n", "번호", "이름", "국어", "영어", "수학", "총점", "평균", "등급", "등수");
						printf(" %d    %s   %d   %d   %d   %d   %.1lf   %c   %d\n", stu[i].number, stu[i].name, stu[i].kor, stu[i].eng, stu[i].any, stu[i].sum, stu[i].avg, stu[i].r, i+1);
						fprintf(fout3, "마지막 검색기록...: %s의 성적", stu[i].name);
						is_find_on = 1;//찾음플래그를 킴 
					}
				}
				if(is_find_on == 0) {
					printf("찾지 못하였습니다..");
					system("pause");
					system("cls");
					main();
				} else {
					system("pause");
					system("cls");
					//is_find_on 초기화를 할 필요가 없음. 메인에서 처음부분에 초기화하니까 
					main();
				}
			} else if(choose == 4) {
				exit(1);//바로종료 
			} else if(choose == 1234){
				printf("이스터에그는 개발자의 숙명이지..ㅋㅋ\n");
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
			printf("파일이 존재하지 않습니다. rank.txt파일을 해당프로그램의 경로에 만들어서 n값과 그다음줄부터 학번, 이름, 국, 영, 수 순으로 값을 입력해주시기 바랍니다.\n");
			system("pause");
			system("cls");
			printf("혹시 모르니까 경로를 입력해주세요 : ");
			scanf("%s", path);
			fin = fopen(path, "r");
			if(checkFerror(fin) == 0) {
				printf("그 파일을 이 프로그램의 경로에 두세요.\n");
				system("pause");
				system("cls");
				main();
			} else {
				system("pause");
				system("cls");
				printf("경로가 없습니다.\n");
				system("pause");
				system("cls");
				exit(1);
			}
		}
	
	return 0;
}
