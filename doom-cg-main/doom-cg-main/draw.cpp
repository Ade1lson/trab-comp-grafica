#include <GL/glut.h>
#include <math.h>
#include "scene.h"

#define NUM_TORRES 5
#define RAIO 10.0f // raio das torres ao redor do centro

// Variáveis para a bicicleta
#define RAIO_RODA 0.3f
#define LARGURA_RODA 0.05f
#define NUM_RAIOS 8 // Número de raios na roda

// Função auxiliar para desenhar uma roda que gira e tem raios
static void desenhaRoda(float x, float y, float z)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    
    // Aplica a rotação da roda no eixo Z local para o giro
    glRotatef(anguloEsfera * 5.0f, 0.0f, 0.0f, 1.0f); 
    
    // Roda (Toro - Pneu)
    glColor3f(0.1f, 0.1f, 0.1f); // Preto
    glutSolidTorus(LARGURA_RODA, RAIO_RODA, 20, 20);

    // Centro da Roda (Hub)
    glColor3f(0.5f, 0.5f, 0.5f); // Cinza
    glutSolidSphere(LARGURA_RODA * 0.5f, 10, 10);

    // --- Desenho dos Raios ---
    glColor3f(0.7f, 0.7f, 0.7f); // Cor dos raios (cinza claro)
    glLineWidth(1.5f);           // Aumenta a largura da linha para melhor visualização

    glBegin(GL_LINES);
    for (int i = 0; i < NUM_RAIOS; i++)
    {
        float anguloRaio = 2.0f * M_PI * i / NUM_RAIOS;
        float rx_ext = RAIO_RODA * cosf(anguloRaio); 
        float ry_ext = RAIO_RODA * sinf(anguloRaio);

        glVertex3f(0.0f, 0.0f, 0.0f); // Começa no centro da roda (hub)
        glVertex3f(rx_ext, ry_ext, 0.0f); // Vai até a borda interna do pneu
    }
    glEnd();
    glLineWidth(1.0f); // Volta a largura da linha padrão
    
    glPopMatrix();
}

void desenhaBicicleta()
{
    float alturaChao = 0.0f;
    float comprimentoCorpo = 1.0f;
    float alturaCorpo = 0.4f;

    // Coordenadas da primeira torre (em Z negativo, para escorar a bicicleta)
    float torreX = RAIO * cosf(-M_PI / 2.0f);
    float torreZ = RAIO * sinf(-M_PI / 2.0f);

    glPushMatrix();
    // Move a bicicleta para perto da primeira torre
    glTranslatef(torreX, alturaChao, torreZ + 1.2f);
    
    // Gira para ficar paralela à torre e inclina para parecer escorada
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(-15.0f, 1.0f, 0.0f, 0.0f); 

    // --- Corpo Principal (Quadro) ---
    glColor3f(0.9f, 0.2f, 0.1f); // Cor principal (Laranja/Vermelho)

    float tuboLargura = LARGURA_RODA * 2.0f;
    
    // 1. Tubo horizontal superior
    glPushMatrix();
    glTranslatef(0.0f, alturaCorpo, 0.0f);
    glScalef(comprimentoCorpo, tuboLargura, tuboLargura);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // 2. Tubo do selim (vertical)
    glPushMatrix();
    glTranslatef(comprimentoCorpo / 2.0f, alturaCorpo / 2.0f, 0.0f);
    glScalef(tuboLargura, alturaCorpo, tuboLargura);
    glutSolidCube(1.0f);
    glPopMatrix();

    // 3. Tubo diagonal inferior
    glPushMatrix();
    glTranslatef(-comprimentoCorpo / 4.0f, alturaCorpo / 2.0f, 0.0f);
    glRotatef(30.0f, 0.0f, 0.0f, 1.0f);
    glScalef(comprimentoCorpo * 0.7f, tuboLargura, tuboLargura);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // --- Rodas ---
    float rodaY = RAIO_RODA;
    desenhaRoda(-comprimentoCorpo / 2.0f, rodaY, 0.0f); // Traseira
    desenhaRoda(comprimentoCorpo / 2.0f, rodaY, 0.0f); // Dianteira

    // --- Selim (Assento) ---
    float selimX = -0.3f; // Posição no tubo vertical
    float selimY = alturaCorpo + tuboLargura; 
    
    glPushMatrix();
    glTranslatef(comprimentoCorpo / 2.0f + selimX, selimY, 0.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f); // Gira para ficar lateral
    glScalef(0.3f, 0.05f, 0.15f); // Forma achatada
    glColor3f(0.15f, 0.15f, 0.15f); // Cor preta
    glutSolidCube(1.0f);
    glPopMatrix();

    // --- Guidão (Handlebars) ---
    float guidaoX = -comprimentoCorpo / 2.0f; // Posição na frente
    float guidaoY = alturaCorpo + tuboLargura;

    // Tubo da direção (simples)
    glPushMatrix();
    glTranslatef(guidaoX, (alturaCorpo + guidaoY) / 2.0f, 0.0f);
    glScalef(tuboLargura, (guidaoY - alturaCorpo) * 0.8f, tuboLargura);
    glColor3f(0.5f, 0.5f, 0.5f); // Cinza
    glutSolidCube(1.0f);
    glPopMatrix();

    // Barra do guidão (horizontal)
    glPushMatrix();
    glTranslatef(guidaoX, guidaoY, 0.0f);
    glScalef(tuboLargura * 0.5f, tuboLargura, 0.5f); // Barra larga
    glColor3f(0.15f, 0.15f, 0.15f); // Preto
    glutSolidCube(1.0f);
    glPopMatrix();

    glPopMatrix(); // Pop principal
}


// O código para desenhaLosango, desenhaChao, desenhaTorresELosangos e desenhaPiramideDegraus segue abaixo inalterado.
static void desenhaLosango(float altura)
{
    float h = altura / 2.0f;
    float s = altura / 3.0f;

    float claro[3] = {0.3f, 1.0f, 0.3f};
    float escuro[3] = {0.0f, 0.6f, 0.0f};

    glBegin(GL_TRIANGLES);
    // metade de cima
    glColor3fv(claro);
    glVertex3f(0.0f, h, 0.0f);
    glVertex3f(-s, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, s);

    glColor3fv(escuro);
    glVertex3f(0.0f, h, 0.0f);
    glVertex3f(0.0f, 0.0f, s);
    glVertex3f(s, 0.0f, 0.0f);

    glColor3fv(claro);
    glVertex3f(0.0f, h, 0.0f);
    glVertex3f(s, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, -s);

    glColor3fv(escuro);
    glVertex3f(0.0f, h, 0.0f);
    glVertex3f(0.0f, 0.0f, -s);
    glVertex3f(-s, 0.0f, 0.0f);

    // metade de baixo
    glColor3fv(claro);
    glVertex3f(0.0f, -h, 0.0f);
    glVertex3f(0.0f, 0.0f, s);
    glVertex3f(-s, 0.0f, 0.0f);

    glColor3fv(escuro);
    glVertex3f(0.0f, -h, 0.0f);
    glVertex3f(s, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, s);

    glColor3fv(claro);
    glVertex3f(0.0f, -h, 0.0f);
    glVertex3f(0.0f, 0.0f, -s);
    glVertex3f(s, 0.0f, 0.0f);

    glColor3fv(escuro);
    glVertex3f(0.0f, -h, 0.0f);
    glVertex3f(-s, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, -s);
    glEnd();
}

void desenhaChao()
{
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex3f(-80.0f, 0.0f, -80.0f);
    glVertex3f(80.0f, 0.0f, -80.0f);
    glVertex3f(80.0f, 0.0f, 80.0f);
    glVertex3f(-80.0f, 0.0f, 80.0f);
    glEnd();
}

void desenhaTorresELosangos()
{
    float alturaTorre = 2.5f;
    float w = 0.7f;

    float ang0 = -M_PI / 2.0f;
    float passo = 2.0f * M_PI / NUM_TORRES;

    for (int i = 0; i < NUM_TORRES; i++)
    {
        float ang = ang0 + passo * i;
        float x = RAIO * cosf(ang);
        float z = RAIO * sinf(ang);

        glPushMatrix();
        glTranslatef(x, 0.0f, z);

        // Torre roxa
        glPushMatrix();
        glColor3f(0.6f, 0.0f, 0.8f);
        glTranslatef(0.0f, alturaTorre / 2.0f, 0.0f);
        glScalef(w, alturaTorre, w);
        glutSolidCube(1.0f);
        glPopMatrix();

        // Losango verde girando em cima 
        glPushMatrix();
        glTranslatef(0.0f, alturaTorre + 1.2f, 0.0f);
        glRotatef(anguloPiramide, 0.0f, 1.0f, 0.0f);
        desenhaLosango(1.5f);
        glPopMatrix();

        glPopMatrix();
    }
}

void desenhaPiramideDegraus()
{
    float alturaDegrau = 0.5f;
    float tamanhoBase = 6.0f;
    float reducao = 0.65f;

    glPushMatrix();

    float roxo1[3] = {0.55f, 0.00f, 0.75f};
    float roxo2[3] = {0.65f, 0.10f, 0.85f};
    float roxo3[3] = {0.75f, 0.20f, 0.95f};

    // Degrau 1
    glColor3f(roxo1[0], roxo1[1], roxo1[2]);
    glPushMatrix();
    glTranslatef(0.0f, alturaDegrau / 2.0f, 0.0f);
    glScalef(tamanhoBase, alturaDegrau, tamanhoBase);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Degrau 2
    glColor3f(roxo2[0], roxo2[1], roxo2[2]);
    glPushMatrix();
    glTranslatef(0.0f, alturaDegrau + alturaDegrau / 2.0f, 0.0f);
    glScalef(tamanhoBase * reducao, alturaDegrau, tamanhoBase * reducao);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Degrau 3
    glColor3f(roxo3[0], roxo3[1], roxo3[2]);
    glPushMatrix();
    glTranslatef(0.0f, 2 * alturaDegrau + alturaDegrau / 2.0f, 0.0f);
    glScalef(tamanhoBase * reducao * reducao,
             alturaDegrau,
             tamanhoBase * reducao * reducao);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Esfera flutuando acima
    float topoDegrausY = 5.0f * alturaDegrau;
    float raioEsfera = 3.0f;

    glPushMatrix();
    glTranslatef(0.0f, topoDegrausY + raioEsfera + 0.2f, 0.0f);

    glRotatef(anguloEsfera, 1.0f, 1.5f, 0.0f);

    double eq[4];

    // metade de cima
    glColor3f(0.40f, 0.00f, 0.00f);
    eq[0] = 0;
    eq[1] = -1;
    eq[2] = 0;
    eq[3] = 0;
    glClipPlane(GL_CLIP_PLANE0, eq);
    glEnable(GL_CLIP_PLANE0);
    glutSolidSphere(raioEsfera, 40, 40);
    glDisable(GL_CLIP_PLANE0);

    // metade de baixo
    glColor3f(0.80f, 0.00f, 0.00f);
    eq[0] = 0;
    eq[1] = 1;
    eq[2] = 0;
    eq[3] = 0;
    glClipPlane(GL_CLIP_PLANE1, eq);
    glEnable(GL_CLIP_PLANE1);
    glutSolidSphere(raioEsfera, 40, 40);
    glDisable(GL_CLIP_PLANE1);

    glPopMatrix();

    glPopMatrix();
}