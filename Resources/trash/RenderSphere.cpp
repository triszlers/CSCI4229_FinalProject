static void Vertex(double th,double ph){
    double x = Sin(th)*Cos(ph);
    double y = Cos(th)*Cos(ph);
    double z =         Sin(ph);
    //  For a sphere at the origin, the position
    //  and normal vectors are the same
    glNormal3d(x,y,z);
    glVertex3d(x,y,z);
}

static void RenderSphere(double tx, double ty, double tz, double r){
    // Save transformation
    glPushMatrix();
    // Offset, scale and rotate
    glTranslated(tx,ty,tz);
    glScaled(r,r,r);
    // White ball with yellow specular
    float yellow[]   = {1.0,1.0,0.0,1.0};
    float Emission[] = {0.0,0.0,0.01f*sun_emission,1.0};
    glColor3f(1,1,0);
    glMaterialf(GL_FRONT,GL_SHININESS,1);            // 1 can be replaced by shiny? value
    glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
    glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
    // Bands of latitude
    for (int ph=-90;ph<90;ph+=sun_increment)
    {
        glBegin(GL_QUAD_STRIP);
        for (int th=0;th<=360;th+=2*sun_increment)
        {
            Vertex(th, ph);
            Vertex(th, ph+sun_increment);
        }
        glEnd();
    }
    //  Undo transofrmations
    glPopMatrix();
}