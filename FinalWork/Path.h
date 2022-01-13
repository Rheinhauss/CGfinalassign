#pragma once
#include "glew.h"
#include "glut.h"
#include "Object.h"

#include <vector>
#include <deque>
class Path :
    public Object
{
    public:
    deque<CVector> pathnodes;//world coordinates
    Path();
    ~Path();

    void Render();
    void Update();
    void update_path(CVector v);//world coordinates
};

