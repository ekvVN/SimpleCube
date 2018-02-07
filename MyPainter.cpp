//
// Created by root on 30.01.18.
//

#include "MyPainter.h"

MyPainter::MyPainter()
    : _model(nullptr)
{
}

void MyPainter::SetModel(Model *model)
{
    _model = model;
}
