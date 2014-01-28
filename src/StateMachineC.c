/*
 ============================================================================
 Name        : StateMachineC.c
 Author      : Adam
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define __DEBUG__

#define __USE_ARR__

#ifdef __DEBUG__
#define DEBUG printf
#else
#define DEBUG(...)
#endif

#define Success 1
#define Fail	0


typedef void (*Func)();

enum {
	STATE_A = 1,
	STATE_B,
	STATE_C,
	STATE_D,
	STATE_MAX = STATE_D,
};

typedef struct _StateMachine StateMachine;

#ifdef __USE_ARR__

struct _StateMachine{
	int state;
	Func pfunc;
};

#else
struct _StateMachine{
	int state;
	Func pfunc;
	StateMachine *next;
};
#endif

//function set
void State_A();
void State_B();
void State_C();
void State_D();

#ifdef __USE_ARR__
//use array
StateMachine stateMap[] = {
		{STATE_A, State_A},
		{STATE_B, State_B},
		{STATE_C, State_C},
		{STATE_D, State_D},
		{0, NULL},
};

void ChangeStateUseArr(int state)
{
	int i = 0;
	int isGet = 0;

	for(i = 0; stateMap[i].state != 0; ++i) {
		if(stateMap[i].state == state) {
			stateMap[i].pfunc();
			isGet = 1;
			break;
		}
	}

	if(!isGet)
		printf("No state function\n");
}
#else

//use pointer
int CeateStateMachineHeader(StateMachine **stateMachine)
{
	int ret = Fail;
	DEBUG("[%s]: \n", __FUNCTION__);

	if(*stateMachine == NULL) {
		*stateMachine = (StateMachine *)malloc(sizeof(StateMachine));
		(*stateMachine)->state = 0;
		(*stateMachine)->pfunc = NULL;
		(*stateMachine)->next = NULL;
		ret = Success;
	}

	return ret;
}

int DeleteStateMachine(StateMachine **stateMachine)
{
	int ret = Fail;
	DEBUG("[%s]: \n", __FUNCTION__);

	if(*stateMachine != NULL) {
		free(*stateMachine);
		*stateMachine = NULL;
		ret = Success;
	}

	return ret;
}

int AddFuncToStateMachine(StateMachine **stateMachine, int state, Func pfunc)
{
	int ret = Fail;
    int startID = 1;
    StateMachine* pre =  NULL;
    StateMachine* new = NULL;

    DEBUG("[%s]: \n", __FUNCTION__);

    pre = *stateMachine;

    while(pre && startID < state){
    	pre = pre->next;
    	startID++;
    }

	if(!pre || startID > state) {
		printf("please initial statemachine\n");
		goto Exit;
	}


	new = (StateMachine*)malloc(sizeof(StateMachine));
	new->state =state;
	new->pfunc = pfunc;
	new->next = pre->next;
	pre->next = new;

	ret = Success;

Exit:
	return ret;
}

int getFunctionFromStateMachine(StateMachine *stateMachine, int state, Func* pfunc)
{
	int ret = Fail;
	int startID = 1;
	DEBUG("[%s]: \n", __FUNCTION__);

	StateMachine* next = NULL;
	next = stateMachine->next;


	if(state == 1) {
		*pfunc = stateMachine->pfunc;
	}

	while(next && startID < state) {
		next = next->next;
		startID++;
	}


	if(!next || startID > state) {
		printf("No state machine\n");
		goto Exit;
	}


	*pfunc = next->pfunc;
	ret = Success;
Exit:
	return ret;
}

int InitialSMTable(StateMachine **stateMachine)
{
	int ret = Fail;
	DEBUG("[%s]: \n", __FUNCTION__);

	if(!*stateMachine) {
		printf("please initial statemachine\n");
		goto Exit;
	}

	AddFuncToStateMachine(stateMachine, STATE_A, State_A);
	AddFuncToStateMachine(stateMachine, STATE_B, State_B);
	AddFuncToStateMachine(stateMachine, STATE_C, State_C);
	AddFuncToStateMachine(stateMachine, STATE_D, State_D);

Exit:
	return ret;
}

void ChangeStateUseLL(StateMachine *stateMachine, int state)
{
	Func pfunc = NULL;
	DEBUG("[%s]: \n", __FUNCTION__);

	if(!stateMachine) {
		printf("please initial statemachine\n");
		return;
	}

	getFunctionFromStateMachine(stateMachine, state, &pfunc);

	if(!pfunc) {
		printf("No state function\n");
	}
	else {
		pfunc();
	}

}

#endif

int main(void) {

#ifdef __USE_ARR__
	int input;

	while(1) {
		printf("Please input number: \n");
		scanf("%d", &input);

		if(input == -1)
			break;

		ChangeStateUseArr(input);
	}
#else
	StateMachine *sm = NULL;
	int input;

	CeateStateMachineHeader(&sm);

	InitialSMTable(&sm);

	while(1) {
		printf("Please input number: \n");
		scanf("%d", &input);

		if(input == -1)
		break;

		ChangeStateUseLL(sm, input);
	}


#endif



//	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	return EXIT_SUCCESS;
}

void State_A()
{
	DEBUG("[%s]: \n", __FUNCTION__);
}

void State_B()
{
	DEBUG("[%s]: \n", __FUNCTION__);
}

void State_C()
{
	DEBUG("[%s]: \n", __FUNCTION__);
}

void State_D()
{
	DEBUG("[%s]: \n", __FUNCTION__);
}
