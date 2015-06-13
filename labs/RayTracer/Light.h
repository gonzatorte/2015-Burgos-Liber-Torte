#ifndef LIGHT_H
#define LIGHT_H


class Light
{
    public:
        Light();
        Light(Vector color, Vector position);
        void read(tinyxml2::XMLElement* element);
        virtual ~Light();
        Color color;
        Vector position;
    protected:
    private:
};

#endif // LIGHT_H
