#ifndef SHADER_H
#define SHADER_H


class Shader
{
    public:
        Shader();
        Colour Shade(int depth,  Intersection inter, Ray ray);
        virtual ~Shader();
    protected:
    private:
};

#endif // SHADER_H
