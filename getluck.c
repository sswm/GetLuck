#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include<time.h>


#define	TEST_TIMES 10000


#define	__DEBUG

#ifdef __DEBUG
#define	SelfPrintf(fmt, args...) printf(fmt, ##args)
#else
#define	SelfPrintf(fmt, ...)
#endif

#define DEBUG_INFO(fmt, args...) printf("\033[33m[%s:%d]\033[0m "#fmt"\r\n", __func__, __LINE__, ##args);

#define	NOW_DISCOUNT		90 //75
#define	DISCOUNT			(float)NOW_DISCOUNT/(float)100
#define	EVERY_BET_POINT			10



//#define	EXTRA_DEAL

#define INPUT_MIN_NUM		0
#define	INPUT_MAX_NUM		9
#define	COMMON_SAME_TIMES   2

//the percentage to win
#define	ALWAYS_TEST_PERCENTAGE	50

#define	WIN_POINT		((float)ALWAYS_TEST_PERCENTAGE/100)

#define	NEED_INPUT_NUMBER	ALWAYS_TEST_PERCENTAGE * (INPUT_MAX_NUM - INPUT_MIN_NUM + 1)/100

#define	BUF_SIZE		1024

#define	NAME_SIZE		100
char name_file[NAME_SIZE] = "haozi";

int totalTimes = 0;
int luckNum = -1;

float nowPoint = 0;

float betPoint = 0;

int nowState = 1;// init win first time


int max_win_times = 0;
int max_lose_times = 0;

int number_array[NEED_INPUT_NUMBER] = {
	#if (ALWAYS_TEST_PERCENTAGE == 20)
	1,2
	#endif	
	#if (ALWAYS_TEST_PERCENTAGE == 30)
	1,2,3
	#endif
	#if (ALWAYS_TEST_PERCENTAGE == 40)
	1,2,4,5
	#endif
	#if (ALWAYS_TEST_PERCENTAGE == 50)
	1,2,3,4,5
	#endif
	#if (ALWAYS_TEST_PERCENTAGE == 60)
	0,1,2,3,4,5
	#endif
	#if (ALWAYS_TEST_PERCENTAGE == 70)
	0,1,2,3,4,5,6
	#endif
	#if (ALWAYS_TEST_PERCENTAGE == 80)
	0,1,2,3,4,5,6,7
	#endif	
};






int SaveYourPoint(float totalPoint);

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
	static int continueWinTimes = 0;
	static int continueFailTimes = 0;
	//int i = 0;
	
	SelfPrintf("Please input your bet point\n");
	if (nowState == 0) {
		#ifdef EXTRA_DEAL
		if (betPoint == (EVERY_BET_POINT * 2)) {
			betPoint = EVERY_BET_POINT;
		} else {
			betPoint *= 2;
		}
		#else
			betPoint *= 2;
			//betPoint *=2;
		#endif
		//betPoint++;//you must add your point if you want to win
		//betPoint = 4;
		//betPoint = 2;//alway fail negative point
		//betPoint = 1;
		continueFailTimes++;
/*
		while(continueFailTimes) {
			continueFailTimes >>= 1;
			if (continueFailTimes) {
				i++;
			}
		}
*/	
		continueWinTimes = 0;

		SelfPrintf("Your bet point is %f continue fail %d times\n", betPoint, continueFailTimes);
		if (continueFailTimes >= COMMON_SAME_TIMES) {
			if (continueFailTimes >= max_lose_times) {
				max_lose_times = continueFailTimes;
			}
			printf("Your bet point is %f continue fail %d times\n", betPoint, continueFailTimes);
			//sleep(2);
			//printf("Continue lose~~\n");
			//sleep(4);
		}
	} else {
		#ifdef EXTRA_DEAL
		betPoint = EVERY_BET_POINT*2;
		#else
		betPoint = EVERY_BET_POINT;
		#endif
		continueWinTimes++;
		continueFailTimes = 0;
		//extra add bet and get more point here
		if(continueWinTimes >= 2) {
			//betPoint = 2;	
			//betPoint++;
			//betPoint *= 3;// equal to betPoint += 3
			//betPoint += 3;
		}
		
		
		
		SelfPrintf("Your bet point is %f continue win %d times\n", betPoint, continueWinTimes);
		if (continueWinTimes >= COMMON_SAME_TIMES) {
			if (continueWinTimes >= max_win_times) {
				max_win_times = continueWinTimes;
			}
			printf("Your bet point is %f continue win %d times\n", betPoint, continueWinTimes);
			//sleep(2);
			//printf("continue win~~\n");
			//sleep(4);
		}
	}
	//scanf("%d", &betPoint);
	
}

void InputWhatYouWant(void) {
	int i;
	SelfPrintf("Please input your %d numbers\n", NEED_INPUT_NUMBER);

	//int inputTimes = NEED_INPUT_NUMBER;
#if 0
	for(i = 0; i < NEED_INPUT_NUMBER, i++){
		scanf("%d", &number_array[i]);
	}
#else	
	//scanf("%d,%d,%d,%d,%d", &number_array[0], &number_array[1], &number_array[2], &number_array[3], &number_array[4]);
	//SafeFlush(stdin);
	#if 0
	for(i = 0; i < NEED_INPUT_NUMBER; i++) {
		if (number_array[i] == luckNum) {
			number_array[i] = (number_array[i] + (rand() % 10))%9;	
		}
	}
	#endif

#endif
	SelfPrintf("Your input number:");
	for(i = 0; i < NEED_INPUT_NUMBER; i++){
		SelfPrintf("%d", number_array[i]);
		if (i != NEED_INPUT_NUMBER - 1) {
			SelfPrintf(",");
		}
	}
	SelfPrintf("\n");
}

void GetLuckNumber(void) {

	srand(clock());
	//srand(time(0));

	luckNum = rand() % 10;

	//SaveYourPoint(luckNum);
	SelfPrintf("The Luck number is %d\n",luckNum);


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


int SaveYourPoint(float totalPoint) {
	static int i = 0;
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
	if (i == 0) {
		i = 1;
		sprintf(buf, "echo 'Your total point is %4f bet is %4f'> %s.txt", totalPoint, betPoint, name_file);
	} else {
		sprintf(buf, "echo 'Your total point is %4f bet is %4f'>> %s.txt", totalPoint, betPoint, name_file);
	}
	system(buf);
#endif
	
	return 0;
}


void CalYourPoint(void) {
	int i;
	float product_value;
	float win_bet_point;

	nowState = 1;
	totalTimes++;
	for (i = 0; i < NEED_INPUT_NUMBER; i++) {
		if (number_array[i] == luckNum) {
			product_value = betPoint/WIN_POINT;
			win_bet_point = product_value*DISCOUNT - betPoint;
			nowPoint += win_bet_point;
			printf("product_value:%f, win_bet_point:%f\n", product_value, win_bet_point);
			//nowPoint += (betPoint*DISCOUNT);
			SelfPrintf("Good Luck! try times:%d\ntotal point:%f\n", totalTimes, nowPoint);	
			return;
		}
	}
	nowPoint -= betPoint;
	nowState = 0;
	SelfPrintf("Poor guy! not win! try times:%d\ntotal point:%f\n", totalTimes, nowPoint);
}

int main(void) {
	int testTimes = TEST_TIMES;
	ShowUsage();
	//InitData();
	//SaveYourPoint(100);

	while(testTimes--) {
		InputYourBetPoint();
		InputWhatYouWant();

		GetLuckNumber();

		CalYourPoint();
		//SaveYourPoint(nowPoint);
		usleep(10);
		//sleep(1);
	}	
	printf("\nYour total point is %f\n", nowPoint);
	printf("%d%s win, every bet point:%d, win:%0.1f discount, testing %d times\n", ALWAYS_TEST_PERCENTAGE, "%", EVERY_BET_POINT, (float)EVERY_BET_POINT*DISCOUNT, TEST_TIMES);
	printf("\nmax win times:%d  max lose times:%d\n", max_win_times, max_lose_times);
	printf("you shall get at lease 2e%d yuan,%d\n", max_lose_times, EVERY_BET_POINT*(1<<max_lose_times));
	return 0;
}
