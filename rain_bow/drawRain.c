/****************************************************************************************
*	File Name				:	drawRain.c
*	CopyRight				:	LPF
*	ModuleName				:	drawRain
*
*	CPU						:   Inter Core 7
*	RTOS					:
*
*	Create Data				:	2015/12/20
*	Author/Corportation		:	Li PeiFeng
*
*	Abstract Description	:	definite the function for drawRaining
*
*--------------------------------Revision History----------------------------------------
*	No	version		Data		Revised By			Item			Description
*	1							LPF									first coding
*
***************************************************************************************/

/****************************************************************************************
*	Include File Section
****************************************************************************************/
#include "drawRain.h"
#include <windows.h>

/*****************************************************************************************
*	Global Variable Declare Section
*****************************************************************************************/
/*��������*/
const GLfloat light_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_diffuse[] = { 1.0f, 0.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 0.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 0.0f, 0.0f, 100.0f, 0.0f };
const GLfloat local_view[] = { GL_TRUE };

/*��������*/
GLfloat shininess[] = { 100.0 };
const GLfloat moonEmission[] = { 0.0, 0.0, 0.0, 1.0 };
const GLfloat moonAmbient[] = { 0.9, 0.9, 0.9, 1.0 };
const GLfloat moonDiffuse[] = { 0.5, 0.5, 0.5, 1.0 };
const GLfloat moonSpecular[] = { 0.5, 0.5, 0.5, 1.0 };
const GLfloat moonPosition [] = { -300.0, 300.0, -100.0, 0.0 };

static float windSpeed = 0.0;			//����
static double increaseCoord = 0.5;		//��������
static double increaseRadius = 0.05;	//�뾶����
static int density = 1;					//����ܶ�,����Ϊ1
static List L;

extern int mainWindow;
extern int controlWindow;
extern int worldWindow;
/****************************************************************************************
*	Function Define Section
****************************************************************************************/
/****************************************************************************************
*@Name............: void initOpenGL(void)
*@Description.....: ��OpenGL���г�ʼ����ʹ�ܸ����ܼ����ù�Դ��
*@Parameters......: void
*@Return values...: void
*@PreCondition....�����ڻ�ͼ֮ǰ�����ã��Ӷ�ʵ�ֹ���
*@PostCondition...����
*****************************************************************************************/
void InitRainScreen(void)
{
	ListNode data[MAX_NUM_OF_NODE];
	srand((unsigned)time(NULL));

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	/*���û�Ͽ����*/
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glLineWidth(1.5);

	/*���ù�������*/
	//glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT1, GL_AMBIENT, moonAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, moonDiffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, moonDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, moonPosition);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);

	InitList(&L);
	CreateDataArray(data, MAX_NUM_OF_NODE, windSpeed);
	CreateList(&L, data, MAX_NUM_OF_NODE);
}

void InitWorld(void)
{
	glClearColor(0.5, 0.5, 0.5, 1.0);
}
void InitControlScreen(void)
{
	glClearColor(0.3, 0.3, 0.3, 1.0);
}
/****************************************************************************************
*@Name............: void ResizeDisplayScreen(int width, int height)
*@Description.....: ���ƴ��ڱ仯�¼�
*@Parameters......: width	:���ڿ���
*					height	:���ڸ߶�
*@Return values...: void
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
void ResizeDisplayScreen(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(120.0, (GLfloat)width / (GLfloat)height, 1.0, 1000.0);//����͸���Ӿ���
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 10.0, 120.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//�������λ��
}

void ResizeWorld(int width, int height)
{
	glViewport(0, 0, width, height);
}
void ResizeControlScreen(int width, int height)
{
	glViewport(0, 0, width, height);
}
//���ݰ뾶radius����Բ
void DrawCircle(double radius)
{
	glBegin(GL_LINE_LOOP);
	for (int j = 0; j < SMOOTH_DEGREE; ++j)
		glVertex2f(radius * cos(2 * PI / SMOOTH_DEGREE * j), radius * sin(2 * PI / SMOOTH_DEGREE * j));
	glEnd();
}

/****************************************************************************************
*@Name............: void DisplayRainScreen(void)
*@Description.....: ���곡����ʾ����
*@Parameters......: void
*@Return values...: void
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
void DisplayRainScreen(void)
{
	ListNode dat;
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�������

	/*��������*/
	glPushMatrix();
	glTranslatef(moonPosition[0], moonPosition[1], moonPosition[2]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, moonSpecular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, moonDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, moonAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, moonEmission);
	glutSolidSphere(10.0, 32, 32);//����һ���ϴ������䵱����
	glPopMatrix();
	for (int i = 1; i <= L.num; ++i)
	{
		GetListIndexNode(&L, i, &dat);

		/*������β�����ɫ*/
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, GetRainDropSpecular(dat.rainDrop));
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, GetRainDropDiffuse(dat.rainDrop));
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, GetRainDropAmbient(dat.rainDrop));
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, GetRainDropShininess(dat.rainDrop));
		glLineWidth(GetWidthOfRainDrop(dat.rainDrop));

		if (Falling == GetRainState(dat.rainDrop))
		{
			GLdouble rainCoord[][3] = { 
				{GetXCoord(dat.rainDrop), GetYCoord(dat.rainDrop), GetZCoord(dat.rainDrop)},
				{GetXCoordEndPoint(dat.rainDrop), GetYCoordEndPoint(dat.rainDrop), GetZCoord(dat.rainDrop)} };//��ȡ��ζ�������
			/*�������*/
			glBegin(GL_LINES);
			glVertex3dv(rainCoord[1]);
			glVertex3dv(rainCoord[0]);
			glEnd();

			if (TRUE == IsTouchWater(dat.rainDrop))//������ˮ�����ж��Ƿ��ת��������������״̬
			{
				ChangeRainStateToMelting(dat.rainDrop);
				Beep(500, 30);//ˮ������
			}
				
			UpdateListNode(&L, i, increaseCoord);//���½������
		}
		else if (Melting == GetRainState(dat.rainDrop))
		{
			/*��������*/
			glPushMatrix();
			glTranslated(GetXCoord(dat.rainDrop), GetYCoord(dat.rainDrop), GetZCoord(dat.rainDrop));//�����������ϵʹ������������䴦����
			glRotatef(90.0, 1.0, 0.0, 0.0);
			DrawCircle(GetCurrentRadius(dat.ripple));
			glPopMatrix();
			UpdateRippleRadius(dat.ripple, increaseRadius);//���������뾶

			if (TRUE == IsRadiusEqualToMax(dat.ripple))//�ж��Ƿ���½��״̬
			{
				ChangeRainStateToDying(dat.rainDrop);
				for (int j = 0; j < density; ++j)//Ԥ�����
				{
					CreateData(&dat, windSpeed);
					InseartList(&L, dat);
				}
			}
				
		}
		else if (Dying == GetRainState(dat.rainDrop))
		{
			DeleteList(&L, i);
			
		/*	increaseCoord = L.num * 0.01 + 0.3;
			increaseRadius = L.num * 0.0001 + 0.03;*/
		}
	}
	
	glutSwapBuffers();
}

void DisplayWorld(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�������
}

void DisplayControlScreen(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�������
}
/****************************************************************************************
*@Name............: void idle(void)
*@Description.....: ���к���
*@Parameters......: void
*@Return values...: void
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
void Idle(void)
{
	glutSetWindow(worldWindow);
	glutPostRedisplay();
	glutSetWindow(controlWindow);
	glutPostRedisplay();
}

/****************************************************************************************
*@Name............: void keyBoard(unsigned char key, int x, int y)
*@Description.....: ������������
*@Parameters......: key		:���µġ�����
*@Return values...: void
*@PreCondition....����
*@PostCondition...����
*****************************************************************************************/
void KeyBoard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27://����"Esc"���˳�
			exit(0);
			break;
	}
}