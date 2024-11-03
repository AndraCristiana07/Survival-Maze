#include "lab_m1/tema2/Tema2.h"

#include <vector>
#include <string>
#include <iostream>
#include <random>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2() {
}


Tema2::~Tema2() {
}

void Tema2::Initialize(Cell Level[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            Level[i][j].display = '*';
            Level[i][j].visited = false;
            Level[i][j].top_wall = true;
            Level[i][j].bot_wall = true;
            Level[i][j].left_wall = true;
            Level[i][j].right_wall = true;
        }
    }
    for (int i = 1; i < SIZE - 1; i++) {
        for (int j = 1; j < SIZE - 1; j++) {
            // Border Cells have fewer accessible walls
            Level[1][j].top_wall = false;
            Level[SIZE - 2][j].bot_wall = false;
            Level[i][1].left_wall = false;
            Level[i][SIZE - 2].right_wall = false;
        }
    }
}

void Tema2::GenerateMaze(Cell level[][SIZE]) {
    // TODO : probabil rando e altfel
//    default_random_engine defEngine;
//    uniform_int_distribution<int> intDistro1(1,SIZE);
//    uniform_int_distribution<int> intDistro2(1,5);
//    uniform_int_distribution<int> intDistro3(1,4);
//    srand(static_cast<unsigned>(time(nullptr)));

    random_device rdev;
//    mt19937 generator(static_cast<unsigned>(time(nullptr))); // Use any constant value you like
    mt19937 generator(rdev()); // Use any constant value you like

    uniform_int_distribution<int> dist(1, SIZE);

    int randomX =  (2 * dist(generator) + 1) % (SIZE - 1);
    int randomY =  (2 * dist(generator) + 1) % (SIZE - 1);

//    int randomX =
//            ((2 * rand()) + 1) % (SIZE - 1);                        // Generate a random odd number between 1 and SIZE
////        ((2 * intDistro1(defEngine)) + 1);                        // Generate a random odd number between 1 and SIZE
//
//    int randomY =
//            ((2 * rand()) + 1) % (SIZE - 1);
////            ((2 * intDistro1(defEngine)) + 1);                        // Generate a random odd number between 1 and SIZE
    posX = randomX;                                                    // Save player's initial X position
    posY = randomY;                                                    // Save player's initial Y position
    int randNoEnemies = 4 + rand() % 5;
//    int randNoEnemies = 4 + intDistro2(defEngine);

    int visitedCells = 1;
    int totalCells = ((SIZE - 1) / 2) * ((SIZE - 1) / 2);
    int percent = 0;
    stack<int> back_trackX, back_trackY;                                // Stack is used to trace the reverse path

    level[randomY][randomX].display = 'S';                                // Set S as the start cell
    level[randomY][randomX].visited = true;                                // Set start cell as visited;
    // TODO : also this
    while (visitedCells < totalCells) {
//        if ((!level[randomY - 2][randomX].visited &&
//             (level[randomY][randomX].top_wall && level[randomY - 2][randomX].bot_wall)) ||
//            (!level[randomY + 2][randomX].visited &&
//             (level[randomY][randomX].bot_wall && level[randomY + 2][randomX].top_wall)) ||
//            (!level[randomY][randomX - 2].visited &&
//             (level[randomY][randomX].left_wall && level[randomY][randomX - 2].right_wall)) ||
//            (!level[randomY][randomX + 2].visited &&
//             (level[randomY][randomX].right_wall && level[randomY][randomX + 2].left_wall))) {

        if ((randomY >= 2 && !level[randomY - 2][randomX].visited &&
             (level[randomY][randomX].top_wall && level[randomY - 2][randomX].bot_wall)) ||
            (randomY <= SIZE - 3 && !level[randomY + 2][randomX].visited &&
             (level[randomY][randomX].bot_wall && level[randomY + 2][randomX].top_wall)) ||
            (randomX >= 2 && !level[randomY][randomX - 2].visited &&
             (level[randomY][randomX].left_wall && level[randomY][randomX - 2].right_wall)) ||
            (randomX <= SIZE - 3 && !level[randomY][randomX + 2].visited &&
             (level[randomY][randomX].right_wall && level[randomY][randomX + 2].left_wall))) {

//        if ((randomY >= 2 && !level[randomY - 2][randomX].visited &&
//             (level[randomY][randomX].top_wall && level[randomY - 2][randomX].bot_wall)) ||
//            (randomY <= SIZE - 3 && !level[randomY + 2][randomX].visited &&
//             (level[randomY][randomX].bot_wall && level[randomY + 2][randomX].top_wall)) ||
//            (randomX >= 2 && !level[randomY][randomX - 2].visited &&
//             (level[randomY][randomX].left_wall && level[randomY][randomX - 2].right_wall)) ||
//            (randomX <= SIZE - 3 && !level[randomY][randomX + 2].visited &&
//             (level[randomY][randomX].right_wall && level[randomY][randomX + 2].left_wall))) {




            int random = (rand() % 4) + 1;        // Pick a random wall 1-4 to knock down
//            int random = intDistro3(defEngine);        // Pick a random wall 1-4 to knock down

            int random2 = (rand() % 4) + 1;        // Pick a random enemy
//            int random2 = intDistro3(defEngine);       // Pick a random enemy

            // GO UP
            if ((random == 1) && (randomY > 1)) {
                if (!level[randomY - 2][randomX].visited) {    // If not visited
                    if (random2 == 1 && randNoEnemies > 0) {
                        level[randomY - 1][randomX].display = 'i';    // Delete display
                        randNoEnemies--;
                        Enemy e;
                        e.remove = false;


                        e.x = randomY - 1 - 0.3f;
                        e.y = 0.2f;

                        e.z = randomX - 0.3f;
                        e.timeExplode = 5;
                        e.explode = false;

                        enemies.push_back(e);

                    } else {
                        level[randomY - 1][randomX].display = ' ';    // Delete display
                    }
                    level[randomY - 1][randomX].visited = true;    // Mark cell as visited
                    level[randomY][randomX].top_wall = false;    // Knock down wall

                    back_trackX.push(randomX);            // Push X for back track
                    back_trackY.push(randomY);            // Push Y for back track

                    randomY -= 2;                    // Move to next cell
                    level[randomY][randomX].visited = true;        // Mark cell moved to as visited
                    level[randomY][randomX].display = ' ';        // Update path
                    level[randomY][randomX].bot_wall = false;    // Knock down wall
                    visitedCells++;                    // Increase visitedCells counter
                } else
                    continue;
            }

                // GO DOWN
            else if ((random == 2) && (randomY < SIZE - 2)) {
                if (!level[randomY + 2][randomX].visited) {    // If not visited

                    if (random2 == 1 && randNoEnemies > 0) {
                        level[randomY + 1][randomX].display = 'i';    // Delete display
                        randNoEnemies--;
                        Enemy e;
                        e.remove = false;


                        e.x = randomY + 1 - 0.3f;

                        e.y = 0.2f;
                        e.z = randomX - 0.3f;
                        e.timeExplode = 5;
                        e.explode = false;


                        enemies.push_back(e);

                    } else {
                        level[randomY + 1][randomX].display = ' ';    // Delete display
                    }
                    level[randomY + 1][randomX].visited = true;    // Mark cell as visited
                    level[randomY][randomX].bot_wall = false;    // Knock down wall

                    back_trackX.push(randomX);            // Push X for back track
                    back_trackY.push(randomY);            // Push Y for back track

                    randomY += 2;                    // Move to next cell
                    level[randomY][randomX].visited = true;        // Mark cell moved to as visited
                    level[randomY][randomX].display = ' ';        // Update path
                    level[randomY][randomX].top_wall = false;    // Knock down wall
                    visitedCells++;                    // Increase visitedCells counter
                } else
                    continue;
            }

                // GO LEFT
            else if ((random == 3) && (randomX > 1)) {
                if (!level[randomY][randomX - 2].visited) {    // If not visited

                    if (random2 == 1 && randNoEnemies > 0) {
                        level[randomY][randomX - 1].display = 'i';    // Delete display
                        randNoEnemies--;
                        Enemy e;
                        e.remove = false;


                        e.x = randomY - 0.3f;
                        e.y = 0.2f;


                        e.z = randomX - 1 - 0.3f;
                        e.timeExplode = 5;
                        e.explode = false;


                        enemies.push_back(e);
                    } else {
                        level[randomY][randomX - 1].display = ' ';    // Delete display
                    }
                    level[randomY][randomX - 1].visited = true;    // Mark cell as visited
                    level[randomY][randomX].left_wall = false;    // Knock down wall

                    back_trackX.push(randomX);            // Push X for back track
                    back_trackY.push(randomY);            // Push Y for back track

                    randomX -= 2;                    // Move to next cell
                    level[randomY][randomX].visited = true;        // Mark cell moved to as visited
                    level[randomY][randomX].display = ' ';        // Update path
                    level[randomY][randomX].right_wall = false;    // Knock down wall
                    visitedCells++;                    // Increase visitedCells counter
                } else
                    continue;
            }

                // GO RIGHT
            else if ((random == 4) && (randomX < SIZE - 2)) {
                if (!level[randomY][randomX + 2].visited) {    // If not visited

                    if (random2 == 1 && randNoEnemies > 0) {
                        level[randomY][randomX + 1].display = 'i';    // Delete display
                        randNoEnemies--;
                        Enemy e;
                        e.remove = false;


                        e.x = randomY - 0.3f;
                        e.y = 0.2f;


                        e.z = randomX + 1 - 0.3f;
                        e.timeExplode = 5;
                        e.explode = false;


                        enemies.push_back(e);
                    } else {
                        level[randomY][randomX + 1].display = ' ';    // Delete display
                    }
                    level[randomY][randomX + 1].visited = true;    // Mark cell as visited
                    level[randomY][randomX].right_wall = false;    // Knock down wall

                    back_trackX.push(randomX);            // Push X for back track
                    back_trackY.push(randomY);            // Push Y for back track

                    randomX += 2;                    // Move to next cell
                    level[randomY][randomX].visited = true;        // Mark cell moved to as visited
                    level[randomY][randomX].display = ' ';        // Update path
                    level[randomY][randomX].left_wall = false;    // Knock down wall
                    visitedCells++;                    // Increase visitedCells counter
                } else
                    continue;
            }


        } else {

            if (!back_trackX.empty()) {
                randomX = back_trackX.top();
                back_trackX.pop();
            }

            if (!back_trackY.empty()) {
                randomY = back_trackY.top();
                back_trackY.pop();
            }
        }


    }

    goalX = randomX;
    goalY = randomY;
    level[goalY][goalX].display = 'E';

}


bool
Tema2::bulletsCollision(float sphereX, float sphereY, float sphereZ, float sphereRadius, float boxMinX, float boxMinY,
                        float boxMinZ,
                        float boxMaxX, float boxMaxY, float boxMaxZ) {
    float x = max(boxMinX, min(sphereX, boxMaxX));
    float y = max(boxMinY, min(sphereY, boxMaxY));
    float z = max(boxMinZ, min(sphereZ, boxMaxZ));


    float distance = sqrt((x - sphereX) * (x - sphereX) +
                          (y - sphereY) * (y - sphereY) +
                          (z - sphereZ) * (z - sphereZ));

    return distance < sphereRadius;
}


bool Tema2::SquareSquareCollision(float aMinX, float aMinY, float aMinZ, float aMaxX, float aMaxY, float aMaxZ,
                                  float bMinX, float bMinY, float bMinZ, float bMaxX, float bMaxY, float bMaxZ) {
    return (aMinX <= bMaxX && aMaxX >= bMinX) &&
           (aMinY <= bMaxY && aMaxY >= bMinY) &&
           (aMinZ <= bMaxZ && aMaxZ >= bMinZ);
}


glm::mat3 Tema2::VisualizationTransf2DUnif(const LogicSpace &logicSpace, const ViewportSpace &viewSpace) {
    float sx, sy, tx, ty, smin;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    if (sx < sy)
        smin = sx;
    else
        smin = sy;
    tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
    ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

    return glm::transpose(glm::mat3(
            smin, 0.0f, tx,
            0.0f, smin, ty,
            0.0f, 0.0f, 1.0f));
}


void Tema2::SetViewportArea(const ViewportSpace &viewSpace, glm::vec3 colorColor, bool clear) {
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float) viewSpace.x, (float) (viewSpace.x + viewSpace.width), (float) viewSpace.y,
                                      (float) (viewSpace.y + viewSpace.height), 0.1f, 400);
    GetSceneCamera()->Update();
}

void Tema2::Init() {

    const string sourceTextureDir = PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "textures");

    // Load textures
    {
        Texture2D *texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "finish.png").c_str(), GL_REPEAT);
        mapTextures["finish"] = texture;
    }

    {
        Texture2D *texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "crate.jpg").c_str(), GL_REPEAT);
        mapTextures["crate"] = texture;
    }

    {
        Texture2D *texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "enemy.png").c_str(), GL_REPEAT);
        mapTextures["enemy"] = texture;
    }
    {
        Texture2D *texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "ground.jpg").c_str(), GL_REPEAT);
        mapTextures["ground"] = texture;
    }
    {
        Texture2D *texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "fire.jpg").c_str(), GL_REPEAT);
        mapTextures["fire"] = texture;
    }

    {
        Texture2D *texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "brown.png").c_str(), GL_REPEAT);
        mapTextures["brown"] = texture;
    }
    {
        Texture2D *texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "skin.jpg").c_str(), GL_REPEAT);
        mapTextures["skin"] = texture;
    }
    {
        Texture2D *texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "kaki.jpeg").c_str(), GL_REPEAT);
        mapTextures["kaki"] = texture;
    }
    {
        Texture2D *texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "wall.jpg").c_str(), GL_REPEAT);
        mapTextures["wall"] = texture;
    }
    {
        Texture2D *texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "floor1.jpg").c_str(), GL_REPEAT);
        mapTextures["floor"] = texture;
    }
    {
        Texture2D *texture = new Texture2D();
        texture->Load2D(PATH_JOIN(sourceTextureDir, "portal.jpg").c_str(), GL_REPEAT);
        mapTextures["portal"] = texture;
    }

    renderCameraTarget = true;
    timer = 0;
    bulletspeed = 2.5f;
    ok = 0;

    enemyx = 0;
    enemyy = 0;
    enemyz = 0;

    posX = 0;
    posY = 0;
    goalX = 0;
    goalY = 0;
    game_over = false;
    direction = 1;

    bodyScaleX = 0.4f;
    bodyScaleZ = 0.2f;

    Initialize(Level);
    GenerateMaze(Level);

    translateX = posY;
    translateZ = posX;
    translateY = 1;

    angularStep = 0;

    camera = new implemented::Camera_tema2();

    camera->Set(glm::vec3(translateX, 4, translateZ - 1), glm::vec3(translateX, translateY, translateZ),
                glm::vec3(0, 1, 0));
    cameraX = camera->position.x;
    cameraY = camera->position.y;
    cameraZ = camera->position.z;
    forward = camera->forward;
    rightt = camera->right;
    upCamera = camera->up;

    logicSpace.x = translateX;       // logic x
    logicSpace.y = translateZ;       // logic y
    logicSpace.width = 4;   // logic width
    logicSpace.height = 4;  // logic height

    healthBarX = 0.5f;
    healthBarY = 1;
    healthLvlX = 0.5f;
    healthLvlY = 1;
    scaleX_healthLvl = 1;
    scaleY_healthLvl = 1;
    scaleY_healthLvl = 1;
    scalex_time = 1;
    scaleY_time = 1;
    glm::vec3 cornerSquare = glm::vec3(0, 0, 0);

    {
        Mesh *healthBar = obj2D::CreateSquare("healthBar", cornerSquare, healthBarX, healthBarY, glm::vec3(1, 0, 0),
                                              false);
        AddMeshToList(healthBar);
    }
    {
        Mesh *healthLvl = obj2D::CreateSquare("healthLvl", cornerSquare, healthLvlX, healthLvlY, glm::vec3(0.1, 0.7, 0),
                                              true);
        AddMeshToList(healthLvl);
    }
    {
        Mesh *timeBar = obj2D::CreateSquare("timeBar", cornerSquare, healthBarX, healthBarY, glm::vec3(1, 0, 1), false);
        AddMeshToList(timeBar);
    }
    {
        Mesh *timeLvl = obj2D::CreateSquare("timeLvl", cornerSquare, healthLvlX, healthLvlY, glm::vec3(0.5, 0.2, 1),
                                            true);
        AddMeshToList(timeLvl);
    }
    {
        Texture2D *texture = new Texture2D();
        texture->Load2D(
                PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "vegetation", "bamboo", "bamboo.png").c_str(),
                GL_REPEAT);
        mapTextures["bamboo"] = texture;
    }


    {
        Mesh *mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh *mesh = new Mesh("plane");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh *mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // TODO(student): After you implement the changing of the projection
    // parameters, remove hardcodings of these parameters
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);


    {
        Shader *shader = new Shader("Tema2Shader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "VertexS.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "FragmentS.glsl"),
                          GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

}


void Tema2::FrameStart() {
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void
Tema2::RenderSimpleMesh2(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, Texture2D *texture1, bool explode,
                         float timeE) {
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = camera->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));


    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // TODO(student): Set any other shader uniforms that you need
    glUniform1i(glGetUniformLocation(shader->program, "explode"), explode);
    glUniform1f(glGetUniformLocation(shader->program, "timeE"), timeE);
    if (texture1) {
        glActiveTexture(GL_TEXTURE0);

        glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());

        glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);

    }

    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}


void Tema2::Update(float deltaTimeSeconds) {


    glm::ivec2 resolution = window->GetResolution();
    auto camera2d = GetSceneCamera();
    camera2d->SetPosition(glm::vec3(0, 0, 50));
    camera2d->SetRotation(glm::vec3(0, 0, 0));
    camera2d->Update();
    viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);

    GetCameraInput()->SetActive(false);
    SetViewportArea(viewSpace, glm::vec3(0), true);


    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);


    DrawScene(visMatrix);

    if (game_over == false) {

        timer -= deltaTimeSeconds;

        scaleY_time -= deltaTimeSeconds / 100;

        if (translateX > goalY - 0.3f && translateZ > goalX - 0.3f &&
            translateX < goalY + 0.3f && translateZ < goalX + 0.3f) {
            cout << "!!!Congratulations!!!\n";
            game_over = true;


        }
        if (scaleY_healthLvl < 0 || scaleY_time < 0) {
            cout << "GAME OVER!!\n";
            game_over = true;

        }
    }


    for (int i = 0; i < SIZE; i++) {

        for (int j = 0; j < SIZE; j++) {
            if (Level[i][j].display == '*') {
                glm::mat4 wall = glm::mat4(1);
                wall = glm::translate(wall, glm::vec3(i, 0.5f, j));
                wall = glm::scale(wall, glm::vec3(1));
                RenderSimpleMesh2(meshes["box"], shaders["Tema2Shader"], wall, mapTextures["wall"], false, 0);
            } else if (Level[i][j].display == 'E') {
                glm::mat4 p = glm::mat4(1);
                p = glm::translate(p, glm::vec3(i, 0, j));
                p = glm::scale(p, glm::vec3(0.02f, 0.02f, 0.02f));
                RenderSimpleMesh2(meshes["plane"], shaders["Tema2Shader"], p, mapTextures["finish"], false, 0);
            } else if (Level[i][j].display == 'S') {

                glm::mat4 p = glm::mat4(1);
                p = glm::translate(p, glm::vec3(i, 0, j));
                p = glm::scale(p, glm::vec3(0.02f, 0.02f, 0.02f));
                RenderSimpleMesh2(meshes["plane"], shaders["Tema2Shader"], p, mapTextures["portal"], false, 0);
            } else {
                glm::mat4 p = glm::mat4(1);
                p = glm::translate(p, glm::vec3(i, 0, j));
                p = glm::scale(p, glm::vec3(0.02f, 0.02f, 0.02f));
                RenderSimpleMesh2(meshes["plane"], shaders["Tema2Shader"], p, mapTextures["floor"], false, 0);

            }
        }
    }
    if (game_over == false) {

        if (enemyz < 0) {
            direction = 4;
            enemyz = 0;
        } else if (enemyx < 0) {
            direction = 1;
            enemyx = 0;
        } else if (enemyx > 0.6f) {
            direction = 3;


        } else if (enemyz > 0.6f) {
            direction = 2;

        }


        if (direction == 1) {
            enemyz += deltaTimeSeconds * 0.3;
        } else if (direction == 2) {
            enemyx += deltaTimeSeconds * 0.3;
        } else if (direction == 3) {
            enemyz -= deltaTimeSeconds * 0.3;

        } else if (direction == 4) {
            enemyx -= deltaTimeSeconds * 0.3;

        }
    }


    for (int i = 0; i < enemies.size(); i++) {
        if (enemies[i].explode == true && enemies[i].remove == false) {
            enemies[i].timeExplode -= deltaTimeSeconds;

            if (enemies[i].timeExplode < 0) {
                enemies[i].remove = true;
            }
        }
        if (enemies[i].remove == false) {
            glm::mat4 p = glm::mat4(1);

            p = glm::translate(p, glm::vec3(enemies[i].x + enemyx, enemies[i].y, enemies[i].z + enemyz));
            p = glm::scale(p, glm::vec3(0.4f, 0.4f, 0.4f));

            RenderSimpleMesh2(meshes["box"], shaders["Tema2Shader"], p, mapTextures["enemy"],
                              enemies[i].explode, enemies[i].timeExplode);

        }
    }


    if (renderCameraTarget) {


        camera->forward = forward;
        camera->right = rightt;
        camera->up = upCamera;

        camera->position.x = cameraX;
        camera->position.y = cameraY;
        camera->position.z = cameraZ;

        glm::mat4 head = glm::mat4(1);
        head = glm::translate(head, glm::vec3(translateX, translateY - 0.05f, translateZ));
        head = glm::scale(head, glm::vec3(0.2f));
        head *= transf3D::RotateOY(angularStep);
        RenderSimpleMesh2(meshes["box"], shaders["Tema2Shader"], head, mapTextures["skin"], false, 0);


        glm::mat4 body = glm::mat4(1);
        body = glm::translate(body, glm::vec3(translateX, translateY - 0.4f, translateZ));
        body = glm::scale(body, glm::vec3(bodyScaleX, 0.5f, bodyScaleZ));
        body *= transf3D::RotateOY(angularStep);
        RenderSimpleMesh2(meshes["box"], shaders["Tema2Shader"], body, mapTextures["kaki"], false, 0);

        glm::mat4 leg1 = glm::mat4(1);
        leg1 = glm::translate(leg1, glm::vec3(translateX, translateY - 0.9f, translateZ));
        leg1 = glm::scale(leg1, glm::vec3(0.18f, 0.5f, 0.2f));
        leg1 *= transf3D::RotateOY(angularStep);
        leg1 = glm::translate(leg1, glm::vec3(-0.55f, 0, 0));
        RenderSimpleMesh2(meshes["box"], shaders["Tema2Shader"], leg1, mapTextures["brown"], false, 0);

        glm::mat4 leg2 = glm::mat4(1);
        leg2 = glm::translate(leg2, glm::vec3(translateX, translateY - 0.9f, translateZ));
        leg2 = glm::scale(leg2, glm::vec3(0.18f, 0.5f, 0.2f));
        leg2 *= transf3D::RotateOY(angularStep);
        leg2 = glm::translate(leg2, glm::vec3(0.55f, 0, 0));
        RenderSimpleMesh2(meshes["box"], shaders["Tema2Shader"], leg2, mapTextures["brown"], false, 0);


        glm::mat4 arm1 = glm::mat4(1);
        arm1 = glm::translate(arm1, glm::vec3(translateX, translateY - 0.3f, translateZ));
        arm1 = glm::scale(arm1, glm::vec3(0.2f, 0.3f, 0.2f));
        arm1 *= transf3D::RotateOY(angularStep);
        arm1 = glm::translate(arm1, glm::vec3(-1.6f, 0, 0));
        RenderSimpleMesh2(meshes["box"], shaders["Tema2Shader"], arm1, mapTextures["kaki"], false, 0);

        glm::mat4 arm2 = glm::mat4(1);
        arm2 = glm::translate(arm2, glm::vec3(translateX, translateY - 0.3f, translateZ));
        arm2 = glm::scale(arm2, glm::vec3(0.2f, 0.3f, 0.2f));
        arm2 *= transf3D::RotateOY(angularStep);
        arm2 = glm::translate(arm2, glm::vec3(+1.6f, 0, 0));
        RenderSimpleMesh2(meshes["box"], shaders["Tema2Shader"], arm2, mapTextures["kaki"], false, 0);

        glm::mat4 arm3 = glm::mat4(1);
        arm3 = glm::translate(arm3, glm::vec3(translateX, translateY - 0.55f, translateZ));
        arm3 = glm::scale(arm3, glm::vec3(0.2f, 0.2f, 0.2f));
        arm3 *= transf3D::RotateOY(angularStep);
        arm3 = glm::translate(arm3, glm::vec3(-1.6f, 0, 0));
        RenderSimpleMesh2(meshes["box"], shaders["Tema2Shader"], arm3, mapTextures["skin"], false, 0);

        glm::mat4 arm4 = glm::mat4(1);
        arm4 = glm::translate(arm4, glm::vec3(translateX, translateY - 0.55f, translateZ));
        arm4 = glm::scale(arm4, glm::vec3(0.2f, 0.2f, 0.2f));
        arm4 *= transf3D::RotateOY(angularStep);
        arm4 = glm::translate(arm4, glm::vec3(+1.6f, 0, 0));
        RenderSimpleMesh2(meshes["box"], shaders["Tema2Shader"], arm4, mapTextures["skin"], false, 0);


    } else {
        camera->position.x = translateX;
        camera->position.y = translateY;
        camera->position.z = translateZ;
    }

    for (int i = 0; i < bullets.size(); i++) {
        if (bullets[i].remove == false) {
            glm::mat4 bul = glm::mat4(1);
            bul = glm::translate(bul, glm::vec3(bullets[i].x, bullets[i].y, bullets[i].z));
            bul = glm::scale(bul, glm::vec3(0.1f));

            RenderMesh(meshes["sphere"], shaders["Color"], bul);
        }

    }


    GetCameraInput()->SetActive(false);

}

void Tema2::DrawScene(glm::mat3 visMatrix) {

    glm::mat3 modelMatrix = glm::mat3(1);
    modelMatrix = visMatrix * transf2D::Translate(logicSpace.x + 5, logicSpace.y + 0.25f);
    RenderMesh2D(meshes["healthBar"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix = visMatrix * transf2D::Translate(logicSpace.x + 5, logicSpace.y + 0.25f);
    modelMatrix *= transf2D::Scale(scaleX_healthLvl, scaleY_healthLvl);
    RenderMesh2D(meshes["healthLvl"], shaders["VertexColor"], modelMatrix);

    glm::mat3 modelMatrix1 = glm::mat3(1);
    modelMatrix1 = visMatrix * transf2D::Translate(logicSpace.x + 5, logicSpace.y + 2.5);
    RenderMesh2D(meshes["timeBar"], shaders["VertexColor"], modelMatrix1);

    modelMatrix1 = glm::mat3(1);
    modelMatrix1 = visMatrix * transf2D::Translate(logicSpace.x + 5, logicSpace.y + 2.5);
    modelMatrix1 *= transf2D::Scale(scalex_time, scaleY_time);
    RenderMesh2D(meshes["timeLvl"], shaders["VertexColor"], modelMatrix1);

}


void Tema2::FrameEnd() {
    DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Tema2::RenderMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix) {
    if (!mesh || !shader || !shader->program)
        return;

    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}


void Tema2::OnInputUpdate(float deltaTime, int mods) {

    if (!game_over) {
        float cameraSpeed = 2.0f;
        float aux = 0;
        int nr_obj = 0;
        if (renderCameraTarget) {

            if (window->KeyHold(GLFW_KEY_W)) {
                angularStep = 0;

                //parcurgem zidurile
                for (int i = 0; i < SIZE; i++) {
                    for (int j = 0; j < SIZE; j++) {
                        if (Level[i][j].display == '*') {
                            if (((i - 0.5f <= translateX + 0.4f && i + 0.5 >= translateX - 0.4f) &&
                                 (j - 0.5f <= translateZ + 0.2f && j + 0.5f >= translateZ - 0.2f))) {
                                nr_obj++;
                            }
                        }
                    }
                }

                if (nr_obj == 0) {
                    translateZ += cameraSpeed * deltaTime;
                    cameraZ += cameraSpeed * deltaTime;
                    logicSpace.y -= 0.001 * deltaTime;

                }
                bodyScaleX = 0.4f;
                bodyScaleZ = 0.2f;

            }
            int nr_obj_A = 0;
            if (window->KeyHold(GLFW_KEY_A)) {

                for (int i = 0; i < SIZE; i++) {
                    for (int j = 0; j < SIZE; j++) {
                        if (Level[i][j].display == '*') {
                            if (((i - 0.5f <= translateX + 0.2f && i + 0.5 >= translateX) &&
                                 (j - 0.5f <= translateZ + 0.2 && j + 0.5f >= translateZ - 0.2))) {
                                nr_obj_A++;
                            }
                        }
                    }
                }

                if (nr_obj_A == 0) {
                    translateX += cameraSpeed * deltaTime;
                    cameraX += cameraSpeed * deltaTime;
                    logicSpace.x += 0.001 * deltaTime;
                }


                bodyScaleX = 0.2f;
                bodyScaleZ = 0.4f;

                angularStep = M_PI / 2;


            }
            int nr_obj_S = 0;
            if (window->KeyHold(GLFW_KEY_S)) {

                for (int i = 0; i < SIZE; i++) {
                    for (int j = 0; j < SIZE; j++) {
                        if (Level[i][j].display == '*') {
                            if (((i - 0.5f <= translateX + 0.4f && i + 0.5 >= translateX - 0.4f) &&
                                 (j - 0.5f <= translateZ - cameraSpeed * deltaTime + 0.2f &&
                                  j + 0.5f >= translateZ - cameraSpeed * deltaTime - 0.2f))) {
                                nr_obj_S++;
                            }
                        }
                    }
                }

                if (nr_obj_S == 0) {
                    translateZ -= cameraSpeed * deltaTime;
                    cameraZ -= cameraSpeed * deltaTime;
                    logicSpace.y += 0.001 * deltaTime;

                }

                bodyScaleX = 0.4f;
                bodyScaleZ = 0.2f;
                angularStep = M_PI;

            }
            int nr_obj_D = 0;
            if (window->KeyHold(GLFW_KEY_D)) {

                for (int i = 0; i < SIZE; i++) {
                    for (int j = 0; j < SIZE; j++) {
                        if (Level[i][j].display == '*') {
                            if (((i - 0.5f <= translateX && i + 0.5 >= translateX - 0.2f) &&
                                 (j - 0.5f <= translateZ + 0.2 && j + 0.5f >= translateZ - 0.2))) {
                                nr_obj_D++;
                            }
                        }
                    }
                }

                if (nr_obj_D == 0) {
                    translateX -= cameraSpeed * deltaTime;
                    cameraX -= cameraSpeed * deltaTime;
                    logicSpace.x -= 0.001 * deltaTime;

                }

                bodyScaleX = 0.2f;
                bodyScaleZ = 0.4f;
                angularStep = 3 * M_PI / 2;

            }


            for (int i = 0; i < enemies.size(); i++) {
                if (enemies[i].remove == false) {
                    if (SquareSquareCollision(translateX - bodyScaleX / 2 - 0.2f, translateY - 0.9f,
                                              translateZ - bodyScaleZ / 2, translateX + bodyScaleX / 2 + 0.2f,
                                              translateY + 0.5f, translateZ + bodyScaleZ / 2,
                                              enemies[i].x + enemyx - 0.15f, enemies[i].y - 0.15f,
                                              enemies[i].z + enemyz - 0.15f,
                                              enemies[i].x + enemyx + 0.15f, enemies[i].y + 0.15f,
                                              enemies[i].z + enemyz + 0.15f)) {

                        scaleY_healthLvl -= 0.01;

                    }
                }
            }
        }


        for (int k = 0; k < bullets.size(); k++) {
            if (bullets[k].remove == false) {
                if (bullets[k].ttl > MAX_TTL) {
                    bullets[k].remove = true;

                } else {
                    for (int i = 0; i < enemies.size(); i++) {
                        if (enemies[i].remove == false && enemies[i].explode == false) {
                            if (bulletsCollision(bullets[k].x, bullets[k].y, bullets[k].z, 0.2f,
                                                 enemies[i].x + enemyx - 0.15f, enemies[i].y - 0.15f,
                                                 enemies[i].z + enemyz - 0.15f,
                                                 enemies[i].x + enemyx + 0.15f, enemies[i].y + 0.15f,
                                                 enemies[i].z + enemyz + 0.15f)) {

                                enemies[i].explode = true;
                                bullets[k].remove = true;

                            }
                        }
                    }
                    for (int i = 0; i < SIZE; i++) {
                        for (int j = 0; j < SIZE; j++) {
                            if (Level[i][j].display == '*') {
                                if (bulletsCollision(bullets[k].x, bullets[k].y, bullets[k].z, 0.2f, i - 0.5f, 0,
                                                     j - 0.5f,
                                                     i + 0.5f, 1, j + 0.5f)) {
                                    bullets[k].remove = true;;
                                }
                            }
                        }
                    }

                    bullets[k].x += deltaTime * bulletspeed * bullets[k].dirX;
                    bullets[k].y += deltaTime * bulletspeed * bullets[k].dirY;
                    bullets[k].z += deltaTime * bulletspeed * bullets[k].dirZ;
                    bullets[k].ttl += deltaTime;
                }
            }
        }
    }
}


void Tema2::OnKeyPress(int key, int mods) {
    // Add key press event
    if (key == GLFW_KEY_T) {
        if (renderCameraTarget && ok == 0) {
            forward = camera->forward;
            rightt = camera->right;
            upCamera = camera->up;

            ok = 1;
        }

        renderCameraTarget = !renderCameraTarget;

    }

}


void Tema2::OnKeyRelease(int key, int mods) {
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
    // Add mouse move event

    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;


        if (window->GetSpecialKeyState() == 0 && renderCameraTarget == false) {

            camera->RotateFirstPerson_OX(-sensivityOX * deltaY);
            camera->RotateFirstPerson_OY(-sensivityOY * deltaX);

        }


    }
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
    // Add mouse button press event

    if (timer <= 0) {
        if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {

            float x1, y1;
            Bullet b;
            b.remove = false;
            b.ttl = 0;

            b.x = translateX;

            b.y = translateY;
            b.z = translateZ;

            b.dirX = camera->forward.x;
            b.dirY = camera->forward.y;
            b.dirZ = camera->forward.z;
            bullets.push_back(b);
            //delay pt bullets
            timer = 0.6f;
        }
    }
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {
}


void Tema2::OnWindowResize(int width, int height) {
}
