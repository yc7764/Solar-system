#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <glut.h>
#include <glaux.h>

float Day[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
float Day_Speed[9] = { 4.7, 3.5, 2.9, 2.4, 2.4, 1.3, 0.96, 0.68, 0.54 };
int Time = 0;
float g_fDistance = -55.0f;
float g_fSpinX    = 0.0f;
float g_fSpinY    = 0.0f;
float eyex=0.0, eyey=2.0, eyez=5.0, fovy=40.0, lookx = 0, looky = 0, lookz = 0;
bool ready = true;
int state = 0;

static POINT ptLastMousePosit;
static POINT ptCurrentMousePosit;
static bool bMousing;

GLUquadricObj *sun, *mercury, *venus, *earth, *moon, *mars, *jupiter, *saturn, *saturn_ring, *uranus, *neptune;
GLuint tex[25];   // Texture Mapping을 하기 위한 Texture 이미지의 개수를 위한 배열 변수

AUX_RGBImageRec *LoadBMP(char *Filename) {  // Bitmap 이미지를 호출한다.
     FILE *File=NULL;

     if (!Filename) return NULL;
     File=fopen(Filename,"r");
     if (File) {
          fclose(File);
          return auxDIBImageLoad(Filename);
     }

     return NULL;
}

void InitLookat() {
	g_fDistance = -55.0f;
	g_fSpinX = 0.0f;
	g_fSpinY = 0.0f;
	eyex = 0.0f;
	eyey = 2.0f;
	eyez = 5.0f;
	lookx = 0.0f;
	looky = 0.0f;
	lookz = 0.0f;
}

void SortLookat() {
	g_fDistance = -27.0f;
	g_fSpinX = 0.0f;
	g_fSpinY = 0.0f;
	state += 1;
	eyex = 14.0f;
	eyey = 0.0f;
	eyez = 5.0f;
	lookx = 14.0f;
	looky = 0.0f;
	lookz = 0.0f;
}

void CloseLookat(unsigned char select) {
	switch (select) {
	case '1' :
		g_fDistance = -0.0f;
		g_fSpinX = 0.0f;
		g_fSpinY = 0.0f;
		eyex = 0.0f;
		eyey = 0.0f;
		eyez = 5.0f;
		lookx = 0.0f;
		looky = 0.0f;
		lookz = 0.0f;
		state = 4;
		break;
	case '2':
		g_fDistance = 4.0f;
		g_fSpinX = 0.0f;
		g_fSpinY = 0.0f;
		eyex = 2.3f;
		eyey = 0.0f;
		eyez = 5.0f;
		lookx = 2.3f;
		looky = 0.0f;
		lookz = 0.0f;
		state = 4;
		break;

	case '3':
		g_fDistance = 2.5f;
		g_fSpinX = 0.0f;
		g_fSpinY = 0.0f;
		eyex = 4.3f;
		eyey = 0.0f;
		eyez = 5.0f;
		lookx = 4.3f;
		looky = 0.0f;
		lookz = 0.0f;
		state = 4;
		break;

	case '4':
		g_fDistance = 2.5f;
		g_fSpinX = 0.0f;
		g_fSpinY = 0.0f;
		eyex = 6.5f;
		eyey = 0.0f;
		eyez = 5.0f;
		lookx = 6.5f;
		looky = 0.0f;
		lookz = 0.0f;
		state = 4;
		break;

	case '5':
		g_fDistance = 3.0f;
		g_fSpinX = 0.0f;
		g_fSpinY = 0.0f;
		eyex = 8.5f;
		eyey = 0.0f;
		eyez = 5.0f;
		lookx = 8.5f;
		looky = 0.0f;
		lookz = 0.0f;
		state = 4;
		break;

	case '6':
		g_fDistance = 0.0f;
		g_fSpinX = 0.0f;
		g_fSpinY = 0.0f;
		eyex = 13.0f;
		eyey = 0.0f;
		eyez = 5.0f;
		lookx = 13.0f;
		looky = 0.0f;
		lookz = 0.0f;
		state = 4;
		break;

	case '7':
		g_fDistance = 2.5f;
		g_fSpinX = 0.0f;
		g_fSpinY = 0.0f;
		eyex = 18.0f;
		eyey = 0.0f;
		eyez = 5.0f;
		lookx = 18.f;
		looky = 0.0f;
		lookz = 0.0f;
		state = 4;
		break;

	case '8':
		g_fDistance = 2.5f;
		g_fSpinX = 0.0f;
		g_fSpinY = 0.0f;
		eyex = 23.0f;
		eyey = 0.0f;
		eyez = 5.0f;
		lookx = 23.0f;
		looky = 0.0f;
		lookz = 0.0f;
		state = 4;
		break;

	case '9':
		g_fDistance = 2.5f;
		g_fSpinX = 0.0f;
		g_fSpinY = 0.0f;
		eyex = 28.0f;
		eyey = 0.0f;
		eyez = 5.0f;
		lookx = 28.0f;
		looky = 0.0f;
		lookz = 0.0f;
		state = 4;
		break;
	}
}

void InitQuadricObj() {
	sun = gluNewQuadric();
	mercury = gluNewQuadric();
	venus = gluNewQuadric();
	earth = gluNewQuadric();
	moon = gluNewQuadric();
	mars = gluNewQuadric();
	jupiter = gluNewQuadric();
	saturn = gluNewQuadric();
	saturn_ring = gluNewQuadric();
	uranus = gluNewQuadric();
	neptune = gluNewQuadric();

	gluQuadricTexture(sun, GL_TRUE);
	gluQuadricTexture(mercury, GL_TRUE);
	gluQuadricTexture(venus, GL_TRUE);
	gluQuadricTexture(earth, GL_TRUE);
	gluQuadricTexture(moon, GL_TRUE);
	gluQuadricTexture(mars, GL_TRUE);
	gluQuadricTexture(jupiter, GL_TRUE);
	gluQuadricTexture(saturn, GL_TRUE);
	gluQuadricTexture(saturn_ring, GL_TRUE);
	gluQuadricTexture(uranus, GL_TRUE);

}

void ProcessSelect(GLuint index[64]) {
	switch (index[3]) {
	case 100: MessageBox(NULL, "태양\n자전주기 : 27일 6시간\n지름 : 1,392,684km\n특징 : 태양계의 중심, 현재 약 45억6700만 살이며, 앞으로 78억년간 더 살 수 있을 것으로 예상.", "Sun", MB_OK); break;
	case 101: MessageBox(NULL, "수성\n자전주기 : 58.64일\n공전주기 : 87.97일\n지름 : 4,879.4km\n태양에서의 거리 : 5790만km\n특징 : 중력이 작아 대기가 거의 없음", "Mercury", MB_OK); break;
	case 102: MessageBox(NULL, "금성\n자전주기 : 243.025일\n공전주기 : 224.701일\n지름 : 12,103.7km\n태양에서의 거리 : 1억 821만km\n특징 : 지구와 크기가 비슷함, 자전 방향이 공전 방향과 반대", "Venus", MB_OK); break;
	case 103: MessageBox(NULL, "지구\n자전주기 : 23시간56분4.1초\n공전주기 : 365.256일\n지름 : 12,756.25km\n태양에서의 거리 : 1억 4,960만km\n특징 : 액체 상태의 물, 풍부한 산소", "Earth", MB_OK); break;
	case 104: MessageBox(NULL, "화성\n자전주기 : 24시간37분\n공전주기 : 686.97일\n지름 : 6,779.2km\n태양에서의 거리 : 2억 2739만km\n특징 : 자전축이 지구와 비슷하여 계절변화가 나타남", "Mars", MB_OK); break;
	case 105: MessageBox(NULL, "목성\n자전주기 : 9시간55분\n공전주기 : 11.86년일\n지름 : 142,984km\n태양에서의 거리 : 7억 7,792만km\n특징 : 크기와 질량이 가장 큼 자전 속도가 가장 빠름", "Jupiter", MB_OK); break;
	case 106: MessageBox(NULL, "토성\n자전주기 : 10시간33분\n공전주기 : 29.45년\n지름 : 120,536km\n태양에서의 거리 : 14억 3,018만km\n특징 : 폭이 넓고 뚜렷한 고리가 있음", "Saturn", MB_OK); break;
	case 107: MessageBox(NULL, "천왕성\n자전주기 : 17시간14분\n공전주기 : 84.02년\n지름 : 51,118km\n태양에서의 거리 : 28억 6,933만km\n특징 : 대기에 메테인 성분이 있어 푸른색으로 보임", "Uranus", MB_OK); break;
	case 108: MessageBox(NULL, "해왕성\n자전주기 : 16시간6분\n공전주기 : 164.8년\n지름 : 49,528km\n태양에서의 거리 : 45억 745만km\n특징 : 대기의 소용돌이인 대흑점이 있음", "Neptune", MB_OK); break;
	default: break;
	}
}

void LoadGLTextures( ) {  
     AUX_RGBImageRec *texRec[25];
     memset(texRec, 0, sizeof(void *)*25);                                                  
	 
	 if ((texRec[0] = LoadBMP("GalaxyTex_PositiveX.bmp")) &&
		 (texRec[1] = LoadBMP("GalaxyTex_NegativeX.bmp")) &&
		 (texRec[2] = LoadBMP("GalaxyTex_NegativeZ.bmp")) &&
		 (texRec[3] = LoadBMP("GalaxyTex_PositiveZ.bmp")) &&
		 (texRec[4] = LoadBMP("GalaxyTex_PositiveY.bmp")) &&
		 (texRec[5] = LoadBMP("GalaxyTex_NegativeY.bmp")) &&
		 (texRec[6] = LoadBMP("sun.bmp")) &&
		 (texRec[7] = LoadBMP("mercury.bmp")) &&
		 (texRec[8] = LoadBMP("venus.bmp")) &&
		 (texRec[9] = LoadBMP("earth.bmp")) &&
		 (texRec[10] = LoadBMP("moon.bmp")) &&
		 (texRec[11] = LoadBMP("mars.bmp")) &&
		 (texRec[12] = LoadBMP("jupiter.bmp")) &&
		 (texRec[13] = LoadBMP("saturn.bmp")) &&
		 (texRec[14] = LoadBMP("uranus.bmp")) &&
		 (texRec[15] = LoadBMP("neptune.bmp")) &&
		 (texRec[16] = LoadBMP("1.bmp")) &&
		 (texRec[17] = LoadBMP("2.bmp")) &&
		 (texRec[18] = LoadBMP("3.bmp")) &&
		 (texRec[19] = LoadBMP("4.bmp")) &&
		 (texRec[20] = LoadBMP("5.bmp")) &&
		 (texRec[21] = LoadBMP("6.bmp")) &&
		 (texRec[22] = LoadBMP("7.bmp")) &&
		 (texRec[23] = LoadBMP("8.bmp")) &&
		 (texRec[24] = LoadBMP("9.bmp"))) {

          for(int i=0; i<25; i++) {
               glGenTextures(1, &tex[i]); 
               glBindTexture(GL_TEXTURE_2D, tex[i]);
               glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
               glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
               glTexImage2D(GL_TEXTURE_2D, 0, 3, texRec[i]->sizeX, texRec[i]->sizeY, 0,
                         GL_RGB, GL_UNSIGNED_BYTE, texRec[i]->data); 
          }
     }

     for(int i=0; i<25; i++) {                                                              
          if(texRec[i]) {
               if(texRec[i]->data) free(texRec[i]->data);
               free(texRec[i]);
          } 
     }

     glEnable(GL_TEXTURE_2D);
     glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
}

void DrawCube()
{
	glPushMatrix();
	glTranslatef(0.5f, 0.0f, 0.5f);
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);	// top face
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);	// front face
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -1.0f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 0.0f, 0.0f); // right face
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);	// left face
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -1.0f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, -1.0f);	//back face
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 0.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, -1.0f, -1.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -1.0f, -1.0f); //bottom face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
	glEnd();
	glPopMatrix();
}

void DrawSkybox() {
	float r = 1000.0f;

	// Skybox의 앞면을 Rendering 한다.
	glBindTexture(GL_TEXTURE_2D, tex[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-r, -r / 2, -r);
	glTexCoord2f(1, 0); glVertex3f(r, -r / 2, -r);
	glTexCoord2f(1, 1); glVertex3f(r, r, -r);
	glTexCoord2f(0, 1); glVertex3f(-r, r, -r);
	glEnd();

	// Skybox의 뒷면을 Rendering 한다.
	glBindTexture(GL_TEXTURE_2D, tex[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(r, -r / 2, r);
	glTexCoord2f(1, 0); glVertex3f(-r, -r / 2, r);
	glTexCoord2f(1, 1); glVertex3f(-r, r, r);
	glTexCoord2f(0, 1); glVertex3f(r, r, r);
	glEnd();

	// Skybox의 오른쪽 면을 Rendering 한다.
	glBindTexture(GL_TEXTURE_2D, tex[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(r, -r / 2, -r);
	glTexCoord2f(1, 0); glVertex3f(r, -r / 2, r);
	glTexCoord2f(1, 1); glVertex3f(r, r, r);
	glTexCoord2f(0, 1); glVertex3f(r, r, -r);
	glEnd();

	// Skybox의 왼쪽 면을 Rendering 한다.
	glBindTexture(GL_TEXTURE_2D, tex[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-r, -r / 2, r);
	glTexCoord2f(1, 0); glVertex3f(-r, -r / 2, -r);
	glTexCoord2f(1, 1); glVertex3f(-r, r, -r);
	glTexCoord2f(0, 1); glVertex3f(-r, r, r);
	glEnd();

	// Skybox의 윗면을 Rendering 한다.
	glBindTexture(GL_TEXTURE_2D, tex[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-r, r, -r);
	glTexCoord2f(1, 0); glVertex3f(r, r, -r);
	glTexCoord2f(1, 1); glVertex3f(r, r, r);
	glTexCoord2f(0, 1); glVertex3f(-r, r, r);
	glEnd();

	// Skybox의 아랫면을 Rendering 한다.
	glBindTexture(GL_TEXTURE_2D, tex[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-r, -r / 2, r);
	glTexCoord2f(1, 0); glVertex3f(r, -r / 2, r);
	glTexCoord2f(1, 1); glVertex3f(r, -r / 2, -r);
	glTexCoord2f(0, 1); glVertex3f(-r, -r / 2, -r);
	glEnd();
}

void DrawSolarSystem() {
	glPushName(100);
	glPushMatrix();
	glRotatef(Time, 0.0f, 1.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, tex[6]);
	gluSphere(sun, 1.3, 20, 16);
	glPushMatrix();
	if (state == 2) {
		glTranslatef(0.0f, 3.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, tex[16]);
		DrawCube();
	}
	glPopMatrix();
	glPopMatrix();
	glPopName();

	glPushName(101);
	glPushMatrix();
	glRotatef(Day[0], 0.0, 1.0, 0.0);
	glTranslatef(2.3, 0.0, 0.0);
	glRotatef(Time, 0.0, 1.0, 0.0);
	glPushMatrix();
	glRotatef(-90, 1.0, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, tex[7]);
	gluSphere(mercury, 0.26, 10, 8);
	glPopMatrix();
	glPushMatrix();
	if (state == 2) {
		glTranslatef(0.0f, 3.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, tex[17]);
		DrawCube();
	}
	glPopMatrix();
	glPopMatrix();
	glPopName();
	
	glPushName(102);
	glPushMatrix();
	glRotatef(Day[1], 0.0, 1.0, 0.0);
	glTranslatef(4.3, 0.0, 0.0);
	glRotatef(Time, 0.0, 1.0, 0.0);
	glPushMatrix();
	glRotatef(-90, 1.0, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, tex[8]);
	gluSphere(venus, 0.6, 10, 8);
	glPopMatrix();
	glPushMatrix();
	if (state == 2) {
		glTranslatef(0.0f, 3.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, tex[18]);
		DrawCube();
	}
	glPopMatrix();
	glPopMatrix();
	glPopName();

	glPushName(103);
	glPushMatrix();
	glRotatef(Day[2], 0.0, 1.0, 0.0);
	glTranslatef(6.5, 0.0, 0.0);
	glRotatef(Time, 0.0, 1.0, 0.0);
	glPushMatrix();
	glRotatef(-90, 1.0, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, tex[9]);
	gluSphere(earth, 0.6, 10, 8);
	glPopMatrix();
	glPopName();
	glPushMatrix();
	if (state == 2) {
		glTranslatef(0.0f, 3.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, tex[19]);
		DrawCube();
	}
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.8, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, tex[10]);
	gluSphere(moon, 0.13, 10, 8);
	glPopMatrix();
	glPopMatrix();

	glPushName(104);
	glPushMatrix();
	glRotatef(Day[4], 0.0, 1.0, 0.0);
	glTranslatef(8.5, 0.0, 0.0);
	glRotatef(Time, 0.0, 1.0, 0.0);
	glPushMatrix();
	glRotatef(-90, 1.0, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, tex[11]);
	gluSphere(mars, 0.5, 10, 8);
	glPopMatrix();
	glPushMatrix();
	if (state == 2) {
		glTranslatef(0.0f, 3.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, tex[20]);
		DrawCube();
	}
	glPopMatrix();
	glPopMatrix();
	glPopName();

	glPushName(105);
	glPushMatrix();
	glRotatef(Day[5], 0.0, 1.0, 0.0);
	glTranslatef(13.0, 0.0, 0.0);
	glRotatef(Time, 0.0, 1.0, 0.0);
	glPushMatrix();
	glRotatef(-90, 1.0, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, tex[12]);
	gluSphere(jupiter, 1.2, 10, 8);
	glPopMatrix();
	glPushMatrix();
	if (state == 2) {
		glTranslatef(0.0f, 3.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, tex[21]);
		DrawCube();
	}
	glPopMatrix();
	glPopMatrix();
	glPopName();

	glPushName(106);
	glPushMatrix();
	glRotatef(Day[6], 0.0, 1.0, 0.0);
	glTranslatef(18.0, 0.0, 0.0);
	glRotatef(Time, 0.0, 1.0, 0.0);
	glPushMatrix();
	glRotatef(-90, 1.0, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, tex[13]);
	gluSphere(saturn, 0.602, 10, 8);
	glPopMatrix();
	glPushMatrix();
	if (state == 2) {
		glTranslatef(0.0f, 3.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, tex[22]);
		DrawCube();
	}
	glPopMatrix();
	glPopMatrix();
	glPopName();

	glPushName(107);
	glPushMatrix();
	glRotatef(Day[7], 0.0, 1.0, 0.0);
	glTranslatef(23, 0.0, 0.0);
	glRotatef(Time, 0.0, 1.0, 0.0);
	glPushMatrix();
	glRotatef(-90, 1.0, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, tex[14]);
	gluSphere(uranus, 0.7, 10, 8);
	glPopMatrix();
	glPushMatrix();
	if (state == 2) {
		glTranslatef(0.0f, 3.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, tex[23]);
		DrawCube();
	}
	glPopMatrix();
	glPopMatrix();
	glPopName();

	glPushName(108);
	glPushMatrix();
	glRotatef(Day[8], 0.0, 1.0, 0.0);
	glTranslatef(28, 0.0, 0.0);
	glRotatef(Time, 0.0, 1.0, 0.0);
	glPushMatrix();
	glRotatef(-90, 1.0, 0.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, tex[15]);
	gluSphere(neptune, 0.7, 10, 8);
	glPopMatrix();
	glPushMatrix();
	if (state == 2) {
		glTranslatef(0.0f, 3.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, tex[24]);
		DrawCube();
	}
	glPopMatrix();
	glPopMatrix();
	glPopName();
}

void MyDisplay( ) {
	glEnable(GL_DEPTH_TEST);
	 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glMatrixMode( GL_MODELVIEW );
     glLoadIdentity();
	 glInitNames();

     glTranslatef( 0.0f, 0.0f, g_fDistance );
     glRotatef( -g_fSpinY, 1.0f, 0.0f, 0.0f );
     glRotatef( -g_fSpinX, 0.0f, 1.0f, 0.0f );

     gluLookAt(eyex, eyey, eyez, lookx, looky, lookz, 0.0, 1.0, 0.0);  // 카메라의 위치를 제어한다.
	 DrawSkybox();
	 DrawSolarSystem();

     glutSwapBuffers();
}

void SelectObjects(GLint x, GLint y) {
	GLuint selectBuff[64];
	GLint hits, viewport[4];

	glSelectBuffer(64, selectBuff);
	glGetIntegerv(GL_VIEWPORT, viewport);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glRenderMode(GL_SELECT);
	glLoadIdentity();
	gluPickMatrix(x, viewport[3] - y, 2, 2, viewport);

	gluPerspective(45.0f, 1.0, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	MyDisplay();

	hits = glRenderMode(GL_RENDER);
	if (hits > 0) ProcessSelect(selectBuff);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void MySpecial(int key, int x, int y) {
     if(key == GLUT_KEY_UP) {
          g_fDistance += 2.0f;
     } else if(key == GLUT_KEY_DOWN) {
          g_fDistance -= 2.0f;
     } else if(key == GLUT_KEY_LEFT) {
          eyex += 1.0f;
     } else if(key == GLUT_KEY_RIGHT) {
          eyex -= 1.0f;
	 }

     glutPostRedisplay();
}

void Mykeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 13:
		if (state == 0)
			state += 1;
		else if (state == 2) {
			SortLookat();
			state = 2;
		}
		break;
	case 27:
		if (state <= 2){
			state = 0;
			InitLookat();
		}
		if (state > 2) {
			state = 1;
			SortLookat();
		}
		break;
	default:
		if(state > 1)
			CloseLookat(key);
		break;
	}
}

void MyMouse(int button, int state, int x, int y) {
     switch (button) {
          case GLUT_LEFT_BUTTON:
               if (state == GLUT_DOWN) {
                    ptLastMousePosit.x = ptCurrentMousePosit.x = x;
                    ptLastMousePosit.y = ptCurrentMousePosit.y = y;
					SelectObjects(ptCurrentMousePosit.x, ptCurrentMousePosit.y);
                    bMousing = true;
               } else 
                    bMousing = false;
                    break;
          case GLUT_MIDDLE_BUTTON:
          case GLUT_RIGHT_BUTTON:
               break;
          default:
               break;
     }

    glutPostRedisplay();
}

void MyMotion(int x, int y) {
     ptCurrentMousePosit.x = x;
     ptCurrentMousePosit.y = y;

     if( bMousing )
     {
          g_fSpinX -= (ptCurrentMousePosit.x - ptLastMousePosit.x);
          g_fSpinY -= (ptCurrentMousePosit.y - ptLastMousePosit.y);
     }

     ptLastMousePosit.x = ptCurrentMousePosit.x;
     ptLastMousePosit.y = ptCurrentMousePosit.y;

     glutPostRedisplay();
}

void MyReshape(int w, int h) {
     glViewport(0,0,w,h);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();

     gluPerspective(fovy, (GLfloat)w/(GLfloat)h, 1.0, 2000.0);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
}

void MyTimer(int value) {
	switch (state) {
	case 0:
		for (int i = 0; i < 9; i++) {
			Day[i] += Day_Speed[i];
			if (Day[i] > 360)
				Day[i] = 0;
		}
		break;
	case 1:
			ready = true;
			for (int i = 0; i < 9; i++) {
				if (Day[i] != 0) {
					ready = false;
					Day[i] += 5;
					if (Day[i] > 360)
						Day[i] = 0;
				}
			}
			if (ready) {
				SortLookat();
			}
		break;
	default:
		break;
	}
	Time = (Time + 2) % 360;
	glutPostRedisplay();
	glutTimerFunc(40, MyTimer, 1);
}

void main(int argc, char **argv) {
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
     glutInitWindowPosition(100, 100);
     glutInitWindowSize(800, 600);
     glutCreateWindow("Skybox");
     LoadGLTextures();
	 InitQuadricObj();
     glutDisplayFunc(MyDisplay);
     glutReshapeFunc(MyReshape);
     glutMouseFunc(MyMouse);
     glutMotionFunc(MyMotion);
	 glutKeyboardFunc(Mykeyboard);
     glutSpecialFunc(MySpecial);
	 glutTimerFunc(40, MyTimer, 1);
     glutMainLoop( );
}
