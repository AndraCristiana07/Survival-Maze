#pragma once

#include "components/simple_scene.h"
#include "components/transform.h"
#include "lab_m1/Tema2/camera.h"
#include "lab_m1/Tema2/transf3D.h"
#include "lab_m1/Tema2/transf2D.h"
#include "lab_m1/Tema2/obj2D.h"
#include <stack>
#include <string>
#include <unordered_map>

#define MAX_TTL 1
#define SIZE 11


namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
    public:
        struct ViewportSpace
        {
            ViewportSpace() : x(0), y(0), width(1), height(1) {}
            ViewportSpace(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        struct LogicSpace
        {
            LogicSpace() : x(0), y(0), width(1), height(1) {}
            LogicSpace(float x, float y, float width, float height)
                : x(x), y(y), width(width), height(height) {}
            float x;
            float y;
            float width;
            float height;
        };
        Tema2();
        ~Tema2();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;
       
        void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        glm::mat3 VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);
        void DrawScene(glm::mat3 visMatrix);
        void SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear);
           
        void RenderSimpleMesh2(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1, bool explode, float timeE);

        // void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1, const glm::vec3& color);
       
        bool bulletsCollision(float sphereX, float sphereY, float sphereZ, float sphereRadius, float boxMinX, float boxMinY, float boxMinZ,
            float boxMaxX, float boxMaxY, float boxMaxZ);
        bool SquareSquareCollision(float aMinX, float aMinY, float aMinZ, float aMaxX, float aMaxY, float aMaxZ,
            float bMinX, float bMinY, float bMinZ, float bMaxX, float bMaxY, float bMaxZ);

    protected:
        implemented::Camera_tema2* camera;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;

        // TODO(student): If you need any other class variables, define them here.
        float left = 0, right = 10, bottom = 0, up = 10, fov = 60, zoomIn = 0.01, zoomOut = 200;
        float timer, bulletspeed;
        float angularStep;
        struct Bullet
        {
            float x{};
            float y{};
            float z{};
            bool remove;
            float dirX{};
            float dirY{};
            float dirZ{};
            float ttl;

        };
        std::vector<Bullet> bullets;
        struct Enemy
        {
            float x{};
            float y{};
            float z{};
          
            bool remove;
            float timeExplode;
            bool explode;
            float ttl;

        };
        std::vector<Enemy> enemies;
        float enemyx, enemyy, enemyz;

        struct Cell
        {
            bool visited;
            bool top_wall;
            bool bot_wall;
            bool left_wall;
            bool right_wall;
            char display;
        };
        bool rot;
        Cell Level[SIZE][SIZE];
        int posX;
        int posY;
        int goalX ;
        int goalY ;
        bool game_over ;
      
        void Initialize(Cell Level[][SIZE]);
        void GenerateMaze(Cell Level[][SIZE]);
        float bodyScaleX, bodyScaleZ;
        float translateX, translateY, translateZ;
   
        float cameraX, cameraY, cameraZ;
        std::unordered_map<std::string, Texture2D*> mapTextures;
       
       
        GLfloat timeExplode;
        glm::vec3 forward;
        glm::vec3 rightt;
        glm::vec3 upCamera;
        int direction;
    
        int ok;
      

        ViewportSpace viewSpace;
        LogicSpace logicSpace;
        glm::mat3 visMatrix;

        float healthBarX ,healthBarY,healthLvlX,healthLvlY,scaleY_healthLvl,scaleX_healthLvl,scaleY_time,scalex_time ;
        

       
    };
}   // namespace m1
