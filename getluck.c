#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include<time.h>


#define INPUT_MIN_NUM		0
#define	INPUT_MAX_NUM		9


#define	ALWAYS_TEST_PERCENTAGE	50
#define	NEED_INPUT_NUMBER	ALWAYS_TEST_PERCENTAGE * (INPUT_MAX_NUM - INPUT_MIN_NUM + 1)/100

#define	BUF_SIZE		1024

#define	NAME_SIZE		100
char name_file[NAME_SIZE] = "haozi";

int totalTimes = 0;
int luckNum = -1;

int nowPoint = 0;

int betPoint = 0;

int number_array[NEED_INPUT_NUMBER];

int SaveYourPoint(int totalPoint);

void SafeFlush(FILE *fp) {

	int ch;
	while(((ch = fgetc(fp)) != EOF) && (ch != '\n'));
}
void ShowUsage(void) {
	 
	system("clear");
	printf("**********Welcom to test your good luck!**********\n");
	printf("**********Your input number is from %d to %d**********\n", INPUT_MIN_NUM, INPUT_MAX_NUM);
	printf("**********Your testing percentage is %d%s**********\n", ALWAYS_TEST_PERCENTAGE, "%");
	printf("**********Please input %d number between %d to %d**********\n", NEED_INPUT_NUMBER, INPUT_MIN_NUM, INPUT_MAX_NUM);
	printf("**********Usage:1,2,4,7,9..and enter**********\n");
	printf("\n\nNow input your name to save you data\n");
	printf("Please input your name here\n");
//	scanf("%s", name_file);
	printf("Your input name is %s\n", name_file);
	printf("Your data will save as \"%s.txt\" in current folder(\"%s\")\n", name_file, "trunk");
}

void InputYourBetPoint(void) {
	printf("Please input your bet point\n");
	scanf("%d", &betPoint);
	printf("Your bet point is %d\n", betPoint);
}

void InputWhatYouWant(void) {
	int i;
	printf("Please input you %d numbers\n", NEED_INPUT_NUMBER);

	//int inputTimes = NEED_INPUT_NUMBER;
#if 0
	for(i = 0; i < NEED_INPUT_NUMBER, i++){
		scanf("%d", &number_array[i]);
	}
#else	
	scanf("%d,%d,%d,%d,%d", &number_array[0], &number_array[1], &number_array[2], &number_array[3], &number_array[4]);
	SafeFlush(stdin);

#endif
	printf("Your input number:");
	for(i = 0; i < NEED_INPUT_NUMBER; i++){
		printf("%d", number_array[i]);
		if (i != NEED_INPUT_NUMBER - 1) {
			printf(",");
		}
	}
	printf("\n");
}

void GetLuckNumber(void) {
	
	srand(time(0));

	luckNum = rand() % 10;

	SaveYourPoint(luckNum);
	printf("The Luck number is %d\n",luckNum);


}
void InitData(void) {
	int fd;

	strcat(name_file, ".txt");
	fd = open(name_file, O_RDWR | O_CREAT, 777);
	if (fd < 0) {

		fprintf(stderr, "open %s file fail, please check!\n", name_file);
	}

	
	close(fd);
}


int SaveYourPoint(int totalPoint) {

#if 0
	
	int fd;
	int ret;
	char buf[BUF_SIZE];



	strcat(name_file, ".txt");
	fd = open(name_file, O_RDWR | O_CREAT);
	if (fd < 0) {

		fprintf(stderr, "open %s file fail, please check!\n", name_file);
	}

	sprintf(buf, "Your total point is %d\n", totalPoint);
	ret = write(fd, buf, strlen(buf));
	
	
	
	close(fd);	
#else
	char buf[BUF_SIZE];
	sprintf(buf, "echo 'Your total point is %d' >> %s.txt", totalPoint, name_file);
	system(buf);
#endif
	
	return 0;
}


void CalYourPoint(void) {
	int i;
	totalTimes++;
	for (i = 0; i < NEED_INPUT_NUMBER; i++) {
		if (number_array[i] == luckNum) {
			nowPoint += betPoint;
			printf("Good Luck! try times:%d\ntotal point:%d\n", totalTimes, nowPoint);	
			return;
		}
	}
	nowPoint -= betPoint;
	printf("Poor guy! not win! try times:%d\ntotal point:%d\n", totalTimes, nowPoint);
}

int main(void) {

	ShowUsage();
	//InitData();
	//SaveYourPoint(100);

	while(1) {
		InputYourBetPoint();
		InputWhatYouWant();

		GetLuckNumber();

		CalYourPoint();
	}	
	return 0;
}
