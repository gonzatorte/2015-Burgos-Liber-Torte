
void sample_use(){
    glBegin(GL_TRIANGLES);
    for (j=0; j<object.polygons_qty; j++)
    {
        //----------------- FIRST VERTEX -----------------
        //Normal coordinates of the first vertex
        glNormal3f( object.normal[ object.polygon[j].a ].x,
                    object.normal[ object.polygon[j].a ].y,
                    object.normal[ object.polygon[j].a ].z);
        // Texture coordinates of the first vertex
        glTexCoord2f( object.mapcoord[ object.polygon[j].a ].u,
                      object.mapcoord[ object.polygon[j].a ].v);
        // Coordinates of the first vertex
        glVertex3f( object.vertex[ object.polygon[j].a ].x,
                    object.vertex[ object.polygon[j].a ].y,
                    object.vertex[ object.polygon[j].a ].z);

        //----------------- SECOND VERTEX -----------------
        //Normal coordinates of the second vertex
        glNormal3f( object.normal[ object.polygon[j].b ].x,
                    object.normal[ object.polygon[j].b ].y,
                    object.normal[ object.polygon[j].b ].z);
        // Texture coordinates of the second vertex
        glTexCoord2f( object.mapcoord[ object.polygon[j].b ].u,
                      object.mapcoord[ object.polygon[j].b ].v);
        // Coordinates of the second vertex
        glVertex3f( object.vertex[ object.polygon[j].b ].x,
                    object.vertex[ object.polygon[j].b ].y,
                    object.vertex[ object.polygon[j].b ].z);

        //----------------- THIRD VERTEX -----------------
        //Normal coordinates of the third vertex
        glNormal3f( object.normal[ object.polygon[j].c ].x,
                    object.normal[ object.polygon[j].c ].y,
                    object.normal[ object.polygon[j].c ].z);
        // Texture coordinates of the third vertex
        glTexCoord2f( object.mapcoord[ object.polygon[j].c ].u,
                      object.mapcoord[ object.polygon[j].c ].v);
        // Coordinates of the Third vertex
        glVertex3f( object.vertex[ object.polygon[j].c ].x,
                    object.vertex[ object.polygon[j].c ].y,
                    object.vertex[ object.polygon[j].c ].z);
    }
    glEnd();
}
