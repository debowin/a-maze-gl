#include "glad/glad.h"
#include "glm/glm.hpp"
#include <iostream>
#include <glm/gtx/transform.hpp>
#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Light.h"
#include "Map.h"

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    Display display(1920, 1080, "aMazeGL by DC");
    Shader shader("../res/basicShader");
    Map gameMap("../res/example3.map");

    glm::vec3 startPos = gameMap.GetStartPos();

    Camera camera(startPos, glm::vec3(0, 0, -1),
                  70.f, display.GetWidth() / (float) display.GetHeight(), 0.01f, 1000.f);

    std::vector<PointLight> pointLights;
    // point lights atop the corners of the map.
    pointLights.emplace_back(
            glm::vec3(2.f, 2.f, 2.f), glm::vec3(-gameMap.GetWidth() / 2.f, 2.f, 0.f), 0
    );
    pointLights.emplace_back(
            glm::vec3(2.f, 2.f, 2.f), glm::vec3(gameMap.GetWidth() / 2.f, 2.f, 0.f), 1
    );
    pointLights.emplace_back(
            glm::vec3(2.f, 2.f, 2.f), glm::vec3(-gameMap.GetWidth() / 2.f, 2.f, -gameMap.GetHeight()), 2
    );
    pointLights.emplace_back(
            glm::vec3(2.f, 2.f, 2.f), glm::vec3(gameMap.GetWidth() / 2.f, 2.f, -gameMap.GetHeight()), 3
    );
    // directional light from the upper right.
    DirectionalLight directionalLight(
            glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0, -1, 0)
    );
    // spot light from user's perspective - flashLight
    SpotLight flashLight(
            glm::vec3(.4f, .4f, .3f), startPos, camera.GetForward(),
            glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f))
    );
    glm::vec3 ambientLight = glm::vec3(0.2f, 0.2f, 0.2f);

    float counter;
    shader.Bind();

    SDL_Event event{};
    float turnAngle, movement, step = 0.03f;
    bool pickUp;

    // global lighting
    shader.setVec3("ambientLight", ambientLight);

    while (true) {
        turnAngle = 0.f;
        movement = 0.f;
        pickUp = false;
        if (SDL_PollEvent(&event)) {
            // if SHIFT is pressed along with any movement or view key, do it twice as fast
            if (event.type == SDL_QUIT) {
                break;
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT) { // If "left" is pressed
                turnAngle = step;
                if (event.key.keysym.mod & KMOD_SHIFT) turnAngle *= 2.f;
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT) { // If "right" is pressed
                turnAngle = -step;
                if (event.key.keysym.mod & KMOD_SHIFT) turnAngle *= 2.f;
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP) { // If "up" is pressed
                movement = 1.f;
                if (event.key.keysym.mod & KMOD_SHIFT) movement *= 1.5f;
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN) { // If "down" is pressed
                movement = -1.f;
                if (event.key.keysym.mod & KMOD_SHIFT) movement *= 1.5f;
            } else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RETURN) { // If "enter" is pressed
                pickUp = true;
            } else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_f) { //If "f" is pressed
                display.toggleFullScreen();
            }
        }

        if (turnAngle)
            camera.turn(turnAngle);

        if (movement) {
            glm::vec3 newPosition = camera.getMove(movement * step);
            // add some offset in checking position to avoid crossover into objects
            glm::vec3 testPosition = camera.getMove(movement * (step + 0.05f));
            int status = gameMap.processMovement(testPosition);
            if (status == STATUS_VALID)
                camera.GetPos() = newPosition;
            else if (status == STATUS_COMPLETE) {
                // courtesy of http://patorjk.com/software/taag
                printf("_____.___.________   ____ ___   __      __.___ _______   \n"
                               "\\__  |   |\\_____  \\ |    |   \\ /  \\    /  \\   |\\      \\  \n"
                               " /   |   | /   |   \\|    |   / \\   \\/\\/   /   |/   |   \\ \n"
                               " \\____   |/    |    \\    |  /   \\        /|   /    |    \\\n"
                               " / ______|\\_______  /______/     \\__/\\  / |___\\____|__  /\n"
                               " \\/               \\/                  \\/              \\/ ");
                break;
            }
        }

        if (pickUp) {
            gameMap.PickUpKey(camera.GetPos());
        }

        for (PointLight pointLight: pointLights)
            pointLight.SetShaderUniform(shader, camera);
        directionalLight.SetShaderUniform(shader, camera);


        counter = SDL_GetTicks() / 1000.f;
        display.Clear(0.0784f, 0.290f, 0.368f, 1.f);

        // dynamic lighting
        flashLight.GetPosition() = camera.GetPos();
        flashLight.GetDirection() = camera.GetForward();
        flashLight.SetShaderUniform(shader, camera);

        gameMap.Draw(shader, camera, counter);

        display.Update();
    }
    return 0;
}