#include <iostream>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/MatrixTransform>
#include <osgGA/TrackballManipulator>
#include <osg/PositionAttitudeTransform>
#include <osg/Texture2D>
#include <osg/TexGen>

// Define a rotation callback class
class SpinCallback : public osg::NodeCallback
{
public:
    virtual void operator()(osg::Node *node, osg::NodeVisitor *nv)
    {
        // Obtener el transformador de actitud de posición desde el nodo
        osg::PositionAttitudeTransform *pat = dynamic_cast<osg::PositionAttitudeTransform *>(node);

        if (pat)
        {
            // Obtener el tiempo de simulación actual
            double time = nv->getFrameStamp()->getSimulationTime();

            // Calcular ángulos de rotación en grados basados en el tiempo
            double angleX = osg::inDegrees(time * 40.0);
            double angleY = osg::inDegrees(time * 30.0);
            double angleZ = osg::inDegrees(time * 20.0);

            // Crear cuaterniones de rotación en cada eje
            osg::Quat rotationX(angleX, osg::Vec3(1, 0, 0));
            osg::Quat rotationY(angleY, osg::Vec3(0, 1, 0));
            osg::Quat rotationZ(angleZ, osg::Vec3(0, 0, 1));

            // Combinar las rotaciones en un cuaternión final
            osg::Quat finalRotation = rotationY * rotationX * rotationZ;

            // Aplicar la rotación al transformador de actitud de posición
            pat->setAttitude(finalRotation);
        }

        // Continuar recorriendo la estructura de nodos
        traverse(node, nv);
    }
};

int main(int argc, char *argv[])
{
    // Verificar los parámetros de la línea de comandos
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <model file>\n";
        exit(1);
    }

    // Cargar el modelo especificado en la línea de comandos
    osg::ref_ptr<osg::Node> loadedModel = osgDB::readNodeFile(argv[1]);
    if (!loadedModel)
    {
        std::cerr << "Problem opening '" << argv[1] << "'\n";
        exit(1);
    }

    // Crear el nodo raíz de la escena
    auto root = new osg::Group();

    // Crear una fuente de luz y configurarla
    auto lightSource = new osg::LightSource();
    lightSource->addChild(loadedModel);
    lightSource->getLight()->setLightNum(1);
    lightSource->getLight()->setPosition(osg::Vec4(5.0, 5.0, 5.0, 1.0));
    lightSource->getLight()->setDiffuse(osg::Vec4(1.0, 0.5, 1.0, 1.0));

    // Configurar el estado para habilitar la luz
    auto state = root->getOrCreateStateSet();
    state->setMode(GL_LIGHT1, osg::StateAttribute::ON);

    // Crear un transformador de actitud de posición para la luz
    auto light = new osg::PositionAttitudeTransform;
    light->addChild(lightSource);
    light->setPosition(osg::Vec3(5.0, 0.0, 1.0));
    light->setScale(osg::Vec3(0.2, 0.2, 0.2));

    // Cargar una textura y aplicarla a los modelos
    auto texture = new osg::Texture2D();
    auto image = osgDB::readImageFile("spinningcube.png");
    texture->setImage(image);

    // Crear un transformador de actitud de posición para el primer cubo
    auto cube1 = new osg::PositionAttitudeTransform;
    cube1->addChild(loadedModel);
    cube1->setUpdateCallback(new SpinCallback);

    // Configurar el estado para aplicar la textura al primer cubo
    auto state_cube1 = cube1->getOrCreateStateSet();
    state_cube1->setTextureAttributeAndModes(0, texture);

    // Crear un transformador de actitud de posición para el segundo cubo
    auto cube2 = new osg::PositionAttitudeTransform;
    cube2->addChild(loadedModel);
    cube2->setPosition(osg::Vec3(2.0, 0.0, 0.0));
    cube2->setUpdateCallback(new SpinCallback);

    // Configurar el estado para aplicar la textura al segundo cubo
    auto state_cube2 = cube2->getOrCreateStateSet();
    state_cube2->setTextureAttributeAndModes(0, texture);

    // Agregar los nodos a la estructura de la escena
    root->addChild(light);
    root->addChild(cube1);
    root->addChild(cube2);

    // Crear un visor para la escena y configurar la estructura de nodos raíz
    osgViewer::Viewer viewer;
    viewer.setSceneData(root);

    // Configurar un manipulador de cámara para la interacción del usuario
    viewer.setCameraManipulator(new osgGA::TrackballManipulator);

    // Iniciar el bucle de renderizado principal
    viewer.run();
}
