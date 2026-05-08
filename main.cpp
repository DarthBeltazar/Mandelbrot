#include <iostream>
#include <SFML/Graphics.hpp>
int main() {
    sf::Shader shader;
    constexpr std::string_view fragmentShader = R"(
#version 120
uniform sampler2D texture;
uniform int maxIterations;
uniform vec3 col;
uniform vec2 screenSize;
uniform float scale;
uniform vec2 centerPos;
vec2 zsquare(vec2 z){
    return vec2(z.x * z.x-z.y*z.y, 2*z.x*z.y);
}
float color(vec2 xy){
    int iter = 0;
    vec2 z = xy;
    for (int i = 0; i < maxIterations; i++){
        z = zsquare(z)+xy;
        if(length(z)>2){
            break;
        }
        iter += 1;
    }
    if (iter == maxIterations) return 1.;
    float dc = log(log(z.x*z.x + z.y*z.y) * 0.5 / log(2.)) / log(2.);
    return (float(iter) + 1. - dc)/float(maxIterations);
}
void main()
{
    vec2 uv = gl_TexCoord[0].xy;
    uv -= vec2(0.5, 0.5);
    uv.x *= screenSize.x/screenSize.y;
    uv *= scale;
    uv += centerPos;
    gl_FragColor = vec4(pow(color(uv), 0.45)) * vec4(col,1);
}

)";
    shader.loadFromMemory(fragmentShader, sf::Shader::Type::Fragment);
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Mandelbrot's set by Alexandr Georgiev");
    sf::View view = window.getView();

    float mws_sens = 1;
    int iterations = 100;
    float scale = 3.f;

    sf::Vector2f center_pos(-1, 0);
    sf::Vector2i oldMousePos(0, 0);


    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                // update the view to the new size of the window
                sf::FloatRect visibleArea({0.f, 0.f}, sf::Vector2f(resized->size));
                window.setView(sf::View(visibleArea));
            }
            else if(const auto* wheelMoved = event->getIf<sf::Event::MouseWheelScrolled>())
            {
                scale -= wheelMoved->delta*scale*0.1f*mws_sens;
            }
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f dMousePos = sf::Vector2f(mousePos) - sf::Vector2f(oldMousePos);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            center_pos -= sf::Vector2f(dMousePos.x * scale / window.getSize().y, dMousePos.y * scale / window.getSize().y);
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
            float di = dMousePos.y / window.getSize().x * 1000;
            iterations = static_cast<int>(static_cast<float>(iterations) + di);
            std::cout << "Iterations: " << iterations << std::endl;
            if (iterations < 1) {
                iterations = 1;
            }
        }
        oldMousePos = mousePos;
        window.setTitle("Mandelbrot's set by Alexandr Georgiev.     Iterations: " + std::to_string(iterations)+"    Center: " + std::to_string(center_pos.x) + " " + std::to_string(center_pos.y));

        window.clear(sf::Color::Black);
        sf::Image image(window.getSize(), sf::Color::Black);
        sf::Texture texture(image);
        shader.setUniform("maxIterations", iterations);
        shader.setUniform("col", sf::Vector3f(0.6, 0.7, 1)); //color
        shader.setUniform("screenSize", sf::Vector2f(window.getSize()));
        shader.setUniform("scale", scale);
        shader.setUniform("centerPos", center_pos);
        sf::Sprite sprite(texture);
        window.draw(sprite, &shader);
        window.display();
    }
    return 0;
}