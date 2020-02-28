
#include"main.h"

class noise_Mods{
public:
    noise_Mods();
    noise::module::Perlin perlin_Mod;
    utils::NoiseMap heightMap;
    utils::NoiseMapBuilderPlane heightMapBuilder;
    utils::RendererImage renderer;
    utils::Image image;
    sf::Vector2f image_Size;
    sf::Image noise_Map_Out;
    sf::Color noise_Color;
    sf::Texture texture;
    void draw(sf::RenderWindow* window);
private:
protected:
};
noise_Mods::noise_Mods(){
    image_Size = sf::Vector2f(1920,1080);

    noise_Map_Out.create(image_Size.x,image_Size.y,sf::Color::White);

    heightMapBuilder.SetSourceModule(perlin_Mod);
    heightMapBuilder.SetDestNoiseMap(heightMap);
    heightMapBuilder.SetDestSize(image_Size.x,image_Size.y);
    heightMapBuilder.SetBounds(100.0,110.0,100.0,110.0);
    heightMapBuilder.Build();
    renderer.SetSourceNoiseMap (heightMap);
    renderer.SetDestImage (image);
    renderer.ClearGradient ();
    renderer.AddGradientPoint (-1.0000, utils::Color (  0,   0, 128, 255)); // deeps
    renderer.AddGradientPoint (-0.2500, utils::Color (  0,   0, 255, 255)); // shallow
    renderer.AddGradientPoint ( 0.0000, utils::Color (  0, 128, 255, 255)); // shore
    renderer.AddGradientPoint ( 0.0625, utils::Color (240, 240,  64, 255)); // sand
    renderer.AddGradientPoint ( 0.1250, utils::Color ( 32, 160,   0, 255)); // grass
    renderer.AddGradientPoint ( 0.3750, utils::Color (224, 224,   0, 255)); // dirt
    renderer.AddGradientPoint ( 0.7500, utils::Color (128, 128, 128, 255)); // rock
    renderer.AddGradientPoint ( 1.0000, utils::Color (255, 255, 255, 255)); // snow
    renderer.EnableLight();
    renderer.SetLightContrast (3.0);
    renderer.SetLightBrightness (2.0);
    renderer.Render();
    for(int x=0;x<image_Size.x;x++){
        for(int y=0;y<image_Size.y;y++){
            noise::utils::Color temp=image.GetValue(x,y);
            noise_Color=sf::Color(temp.red,temp.green,temp.blue);
            noise_Map_Out.setPixel(x,y,noise_Color);
        }
    }
    texture.loadFromImage(noise_Map_Out,sf::IntRect(0.0,0.0,image_Size.x,image_Size.y));
}
void noise_Mods::draw(sf::RenderWindow* window){
    window->draw(sf::Sprite(texture));
}
//Contain the scene as a whole
class sfml_Window{
public:
    sfml_Window();
    sf::RenderWindow* get_Window_Pointer();
private:
    sf::RenderWindow window;
protected:
};
sfml_Window::sfml_Window(){

}
sf::RenderWindow* sfml_Window::get_Window_Pointer(){
    return &window;
}

//Any thing that requires any kind of data storage inside the scene
class object{
public:
    object();
private:
    sf::Sprite self_Sprite;
    sf::Vector2f velocity;
protected:
};
object::object(){

}

int main(){

    sfml_Window window;
    noise_Mods mods;
    sf::RenderWindow* window_Pointer=window.get_Window_Pointer();
    window_Pointer->create(sf::VideoMode(1920,1080),"Lines!");
    window_Pointer->setVerticalSyncEnabled(true);
    sf::Event event;
    while(window_Pointer->isOpen()){
        while(window_Pointer->pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                    window_Pointer->close();
                break;
            }
        }
        window_Pointer->clear(sf::Color::Black);
        mods.draw(window_Pointer);
        window_Pointer->display();
    }
    return 1;
}
