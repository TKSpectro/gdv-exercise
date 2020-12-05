
#include "yoshix_fix_function.h"

#include <math.h>
#include <windows.h>

using namespace gfx;

namespace
{
    double    g_Frequency;
    long long g_StartTick;
} // namespace

namespace
{
    void GetFrequency()
    {
        long long Frequency;

        ::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&Frequency));

        g_Frequency = static_cast<double>(Frequency);
    }

    // -----------------------------------------------------------------------------

    void StartTime()
    {
        ::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&g_StartTick));
    }

    // -----------------------------------------------------------------------------

    double GetTimeInSeconds()
    {
        long long CurrentRealTimeTick;

        ::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&CurrentRealTimeTick));

        return static_cast<double>(CurrentRealTimeTick - g_StartTick) / g_Frequency;
    }
} // namespace

namespace
{
    class CApplication : public IApplication
    {
        public:

            CApplication();
            virtual ~CApplication();

        private:

            float   m_FieldOfViewY;     // Vertical view angle of the camera.

            float   m_AngleX;           // Angle of the cube around the x-axis.
            float   m_AngleY;           // Angle of the cube around the y-axis.
            float   m_AngleZ;           // Angle of the cube around the z-axis.

            BHandle m_pCubeMesh;        // A pointer to a YoshiX mesh, which represents a single cube.

        private:

            virtual bool InternOnStartup();
            virtual bool InternOnShutdown();
            virtual bool InternOnCreateMeshes();
            virtual bool InternOnReleaseMeshes();
            virtual bool InternOnResize(int _Width, int _Height);
            virtual bool InternOnUpdate();
            virtual bool InternOnFrame();
    };
} // namespace

namespace
{
    CApplication::CApplication()
        : m_FieldOfViewY(60.0f)     // Set the vertical view angle of the camera to 60 degrees.
        , m_AngleX      (0.0f)
        , m_AngleY      (0.0f)
        , m_AngleZ      (0.0f)
        , m_pCubeMesh   (nullptr)
    {
    }

    // -----------------------------------------------------------------------------

    CApplication::~CApplication()
    {
    }

    // -----------------------------------------------------------------------------

    bool CApplication::InternOnStartup()
    {
        // -----------------------------------------------------------------------------
        // Define the background color of the window. Colors are always 4D tuples,
        // whereas the components of the tuple represent the red, green, blue, and alpha 
        // channel. The alpha channel indicates the transparency of the color. A value
        // of 1 means the color is completely opaque. A value of 0 means the color is
        // completely transparent. The channels red, green, and blue also are values
        // 0..1 with 0 indicating the minimum intensity and 1 the maximum intensity.
        // -----------------------------------------------------------------------------
        float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f, };

        SetClearColor(ClearColor);

        return true;
    }

    // -----------------------------------------------------------------------------

    bool CApplication::InternOnShutdown()
    {
        return true;
    }

    // -----------------------------------------------------------------------------

    bool CApplication::InternOnCreateMeshes()
    {
        // -----------------------------------------------------------------------------
        // Define the vertices of the mesh and their attributes.
        // -----------------------------------------------------------------------------
        static const float s_HalfEdgeLength = 1.0f;
        
        static float s_CubeVertices[][3] =
        {
            { -s_HalfEdgeLength, -s_HalfEdgeLength, -s_HalfEdgeLength, },
            {  s_HalfEdgeLength, -s_HalfEdgeLength, -s_HalfEdgeLength, },
            {  s_HalfEdgeLength,  s_HalfEdgeLength, -s_HalfEdgeLength, },
            { -s_HalfEdgeLength,  s_HalfEdgeLength, -s_HalfEdgeLength, },

            {  s_HalfEdgeLength, -s_HalfEdgeLength, -s_HalfEdgeLength, },
            {  s_HalfEdgeLength, -s_HalfEdgeLength,  s_HalfEdgeLength, },
            {  s_HalfEdgeLength,  s_HalfEdgeLength,  s_HalfEdgeLength, },
            {  s_HalfEdgeLength,  s_HalfEdgeLength, -s_HalfEdgeLength, },

            {  s_HalfEdgeLength, -s_HalfEdgeLength,  s_HalfEdgeLength, },
            { -s_HalfEdgeLength, -s_HalfEdgeLength,  s_HalfEdgeLength, },
            { -s_HalfEdgeLength,  s_HalfEdgeLength,  s_HalfEdgeLength, },
            {  s_HalfEdgeLength,  s_HalfEdgeLength,  s_HalfEdgeLength, },

            { -s_HalfEdgeLength, -s_HalfEdgeLength,  s_HalfEdgeLength, },
            { -s_HalfEdgeLength, -s_HalfEdgeLength, -s_HalfEdgeLength, },
            { -s_HalfEdgeLength,  s_HalfEdgeLength, -s_HalfEdgeLength, },
            { -s_HalfEdgeLength,  s_HalfEdgeLength,  s_HalfEdgeLength, },

            { -s_HalfEdgeLength,  s_HalfEdgeLength, -s_HalfEdgeLength, },
            {  s_HalfEdgeLength,  s_HalfEdgeLength, -s_HalfEdgeLength, },
            {  s_HalfEdgeLength,  s_HalfEdgeLength,  s_HalfEdgeLength, },
            { -s_HalfEdgeLength,  s_HalfEdgeLength,  s_HalfEdgeLength, },

            { -s_HalfEdgeLength, -s_HalfEdgeLength,  s_HalfEdgeLength, },
            {  s_HalfEdgeLength, -s_HalfEdgeLength,  s_HalfEdgeLength, },
            {  s_HalfEdgeLength, -s_HalfEdgeLength, -s_HalfEdgeLength, },
            { -s_HalfEdgeLength, -s_HalfEdgeLength, -s_HalfEdgeLength, },
        };

        static float s_CubeColors[][4] =
        {
            { 1.0f, 0.0f, 0.0f, 1.0f, },
            { 1.0f, 0.0f, 0.0f, 1.0f, },
            { 1.0f, 0.0f, 0.0f, 1.0f, },
            { 1.0f, 0.0f, 0.0f, 1.0f, },

            { 0.0f, 1.0f, 0.0f, 1.0f, },
            { 0.0f, 1.0f, 0.0f, 1.0f, },
            { 0.0f, 1.0f, 0.0f, 1.0f, },
            { 0.0f, 1.0f, 0.0f, 1.0f, },

            { 0.0f, 0.0f, 1.0f, 1.0f, },
            { 0.0f, 0.0f, 1.0f, 1.0f, },
            { 0.0f, 0.0f, 1.0f, 1.0f, },
            { 0.0f, 0.0f, 1.0f, 1.0f, },

            { 1.0f, 1.0f, 0.0f, 1.0f, },
            { 1.0f, 1.0f, 0.0f, 1.0f, },
            { 1.0f, 1.0f, 0.0f, 1.0f, },
            { 1.0f, 1.0f, 0.0f, 1.0f, },

            { 0.0f, 1.0f, 1.0f, 1.0f, },
            { 0.0f, 1.0f, 1.0f, 1.0f, },
            { 0.0f, 1.0f, 1.0f, 1.0f, },
            { 0.0f, 1.0f, 1.0f, 1.0f, },

            { 1.0f, 1.0f, 1.0f, 1.0f, },
            { 1.0f, 1.0f, 1.0f, 1.0f, },
            { 1.0f, 1.0f, 1.0f, 1.0f, },
            { 1.0f, 1.0f, 1.0f, 1.0f, },
        };

        // -----------------------------------------------------------------------------
        // Define the topology of the mesh via indices. An index addresses a vertex from
        // the array above. Three indices represent one triangle. When defining the 
        // triangles of a mesh imagine that you are standing in front of the triangle 
        // and looking to the center of the triangle. If the mesh represents a closed
        // body such as a cube, your view position has to be outside of the body. Now
        // define the indices of the addressed vertices of the triangle in counter-
        // clockwise order.
        // -----------------------------------------------------------------------------
        static int s_CubeIndices[][3] =
        {
            {  0,  1,  2, },
            {  0,  2,  3, },

            {  4,  5,  6, },
            {  4,  6,  7, },

            {  8,  9, 10, },
            {  8, 10, 11, },

            { 12, 13, 14, },
            { 12, 14, 15, },

            { 16, 17, 18, },
            { 16, 18, 19, },

            { 20, 21, 22, },
            { 20, 22, 23, },
        };

        // -----------------------------------------------------------------------------
        // Define the mesh and its material. The material defines the look of the
        // surface covering the mesh. If the material should contain normals, colors, or
        // texture coordinates then their number has to match the number of vertices.
        // If you do not support normals in a mesh, YoshiX will not apply lighting to
        // this mesh. A textured mesh always has to contain texture coordinates and a
        // handle to a texture. A mesh always has to contain vertices and indices.
        // -----------------------------------------------------------------------------
        SMeshInfo MeshInfo;

        MeshInfo.m_pVertices        = &s_CubeVertices[0][0];
        MeshInfo.m_pNormals         = nullptr;                          // No normals
        MeshInfo.m_pColors          = &s_CubeColors[0][0];
        MeshInfo.m_pTexCoords       = nullptr;                          // No texture coordinates
        MeshInfo.m_NumberOfVertices = 24;
        MeshInfo.m_NumberOfIndices  = 36;
        MeshInfo.m_pIndices         = &s_CubeIndices[0][0];
        MeshInfo.m_pTexture         = nullptr;                          // No texture

        CreateMesh(MeshInfo, &m_pCubeMesh);

        return true;
    }

    // -----------------------------------------------------------------------------

    bool CApplication::InternOnReleaseMeshes()
    {
        // -----------------------------------------------------------------------------
        // Important to release the mesh again when the application is shut down.
        // -----------------------------------------------------------------------------
        ReleaseMesh(m_pCubeMesh);

        return true;
    }

    // -----------------------------------------------------------------------------

    bool CApplication::InternOnResize(int _Width, int _Height)
    {
        float ProjectionMatrix[16];

        // -----------------------------------------------------------------------------
        // The projection matrix defines the size of the camera frustum. The YoshiX
        // camera has the shape of a pyramid with the eye position at the top of the
        // pyramid. The horizontal view angle is defined by the vertical view angle
        // and the ratio between window width and window height.
        // -----------------------------------------------------------------------------
        GetProjectionMatrix(m_FieldOfViewY, static_cast<float>(_Width) / static_cast<float>(_Height), 0.1f, 100.0f, ProjectionMatrix);

        SetProjectionMatrix(ProjectionMatrix);

        return true;
    }

    // -----------------------------------------------------------------------------

    bool CApplication::InternOnUpdate()
    {
        float Eye[3];
        float At [3];
        float Up [3];

        float ViewMatrix[16];

        // -----------------------------------------------------------------------------
        // Define position and orientation of the camera in the world.
        // -----------------------------------------------------------------------------
        Eye[0] =   0.0f; At[0] = 0.0f; Up[0] = 0.0f;
        Eye[1] =   0.0f; At[1] = 0.0f; Up[1] = 1.0f;
        Eye[2] = -30.0f; At[2] = 0.0f; Up[2] = 0.0f;

        GetViewMatrix(Eye, At, Up, ViewMatrix);

        SetViewMatrix(ViewMatrix);

        return true;
    }

    // Define all needed variables

    float angle = 0.0f;
    float angleStep = 0.2f;

    float posX = 0.0f;
    float posY = -5.0f;
    float stepX = 0.2f;

    float LocalMatrixE0[16];
    float GlobalMatrixE0[16];
    float ScaleMatrixE0[16];
          
    float LocalMatrixE1[16];
    float GlobalMatrixE1[16];
    float ScaleMatrixE1[16];
    float LocalMatrixE1T[16];
    float LocalMatrixE1R[16];
    float LocalMatrixE1_T[16];
          
    float LocalMatrixE2[16];
    float GlobalMatrixE2[16];
    float ScaleMatrixE2[16];
    float LocalMatrixE2T[16];
    float LocalMatrixE2R[16];
    float LocalMatrixE2_T[16];

    float WorldMatrixE0[16];
    float WorldMatrixE1[16];
    float WorldMatrixE2[16];

    bool CApplication::InternOnFrame()
    {
        // MOVE LEFT-RIGHT
        /*
        posX += stepX;

        if(posX < -8.0f || posX > 8.0f)
        {
            stepX = -stepX;
        }
        */

        //ROTATE ANGLES
        angle += angleStep;

        if(angle < -45.0f || angle > 45.0f)
        {
            angleStep = -angleStep;
        }

        /* ----------------------------Cube1---------------------------- */

        //Calculate LocalMatrixE0     (T)
        GetTranslationMatrix(posX, posY, 0.0f, LocalMatrixE0);

        //Calculate GlobalMatrixE0    (GlobalMatrixE0 = LocalMatrixE0)
        for(int i = 0; i < 16; i++)
        {
            GlobalMatrixE0[i] = LocalMatrixE0[i];
        }

        //Calculate ScaleMatrixE0     (2.5, 4, 2.5)
        GetScaleMatrix(2.5, 4, 2.5, ScaleMatrixE0);

        //WorldMatrixE0 = ScaleMatrixE0 x GlobalMatrixE0
        MulMatrix(ScaleMatrixE0, GlobalMatrixE0, WorldMatrixE0);

        //SetWorldMatrix(WorldMatrixE0)
        SetWorldMatrix(WorldMatrixE0);

        //DrawMesh(m_pQuadMesh)
        DrawMesh(m_pCubeMesh);


        /* ----------------------------Cube2---------------------------- */

        //Calculate LocalMatrixE1     (TR-T)
        GetTranslationMatrix(0, 4, 0.0f, LocalMatrixE1T);
        GetRotationZMatrix(angle, LocalMatrixE1R);
        GetTranslationMatrix(0, -4, 0.0f, LocalMatrixE1_T);
        MulMatrix(LocalMatrixE1T, LocalMatrixE1R, LocalMatrixE1);
        MulMatrix(LocalMatrixE1, LocalMatrixE1_T, LocalMatrixE1);
        MulMatrix(LocalMatrixE1, GetTranslationMatrix(0, 8, 0.0f, LocalMatrixE1T), LocalMatrixE1);
        
        //Calculate GlobalMatrixE1    (GlobalMatrixE1 = LocalMatrixE1 x GlobalMatrixE0)
        MulMatrix(LocalMatrixE1, GlobalMatrixE0, GlobalMatrixE1);

        //Calculate ScaleMatrixE1     (1.5, 4, 1.5)
        GetScaleMatrix(1.5, 4, 1.5, ScaleMatrixE1);

        //WorldMatrixE1 = ScaleMatrixE1 x GlobalMatrixE1
        MulMatrix(ScaleMatrixE1, GlobalMatrixE1, WorldMatrixE1);

        //SetWorldMatrix(WorldMatrixE1)
        SetWorldMatrix(WorldMatrixE1);

        //DrawMesh(m_pQuadMesh)
        DrawMesh(m_pCubeMesh);

        /* ----------------------------Cube3---------------------------- */

        //Calculate LocalMatrixE2     (TR-T)
        GetTranslationMatrix(0, 4, 0.0f, LocalMatrixE2T);
        GetRotationZMatrix(angle, LocalMatrixE2R);
        GetTranslationMatrix(0, -4, 0.0f, LocalMatrixE2_T);
        MulMatrix(LocalMatrixE2T, LocalMatrixE2R, LocalMatrixE2);
        MulMatrix(LocalMatrixE2, LocalMatrixE2_T, LocalMatrixE2);
        MulMatrix(LocalMatrixE2, GetTranslationMatrix(0, 8, 0.0f, LocalMatrixE2T), LocalMatrixE2);

        //Calculate GlobalMatrixE2(GlobalMatrixE2 = LocalMatrixE2 x GlobalMatrixE1)
        MulMatrix(LocalMatrixE2, GlobalMatrixE1, GlobalMatrixE2);

        //Calculate ScaleMatrixE2(0.5, 4, 0.5)
        GetScaleMatrix(0.5, 4, 0.5, ScaleMatrixE2);

        //WorldMatrixE2 = ScaleMatrixE2 x GlobalMatrixE2
        MulMatrix(ScaleMatrixE2, GlobalMatrixE2, WorldMatrixE2);

        //SetWorldMatrix(WorldMatrixE2)
        SetWorldMatrix(WorldMatrixE2);

        //DrawMesh(m_pQuadMesh)
        DrawMesh(m_pCubeMesh);

        return true;
    }
} // namespace

void main()
{
    GetFrequency();
    StartTime();

    CApplication Application;

    RunApplication(800, 600, "YoshiX Example", &Application);
}