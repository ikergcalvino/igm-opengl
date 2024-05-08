#include <iostream>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osg/MatrixTransform>
#include <osgGA/TrackballManipulator>
#include <osg/PositionAttitudeTransform>

// Define a rotation callback class
class SpinCallback : public osg::NodeCallback
{
public:
    virtual void operator()(osg::Node* node, osg::NodeVisitor* nv)
    {
        osg::PositionAttitudeTransform* pat = dynamic_cast<osg::PositionAttitudeTransform*>(node);
        if (pat)
        {
            double time = nv->getFrameStamp()->getSimulationTime(); // Tiempo de simulación en segundos

            // Calcular ángulos de rotación en grados para cada eje
            double angleX = osg::inDegrees(time * 40.0); // Rotación en el eje X
            double angleY = osg::inDegrees(time * 30.0); // Rotación en el eje Y
            double angleZ = osg::inDegrees(time * 20.0); // Rotación en el eje Z

            // Crear cuaternión acumulando las rotaciones sobre cada eje
            osg::Quat rotationX(angleX, osg::Vec3(1, 0, 0)); // Rotación alrededor del eje X
            osg::Quat rotationY(angleY, osg::Vec3(0, 1, 0)); // Rotación alrededor del eje Y
            osg::Quat rotationZ(angleZ, osg::Vec3(0, 0, 1)); // Rotación alrededor del eje Z

            // Combinar las rotaciones en un solo cuaternión (en orden Y, X, Z)
            osg::Quat finalRotation = rotationY * rotationX * rotationZ;

            // Aplicar la rotación al PositionAttitudeTransform
            pat->setAttitude(finalRotation);
        }

        // Continuar la visita a los nodos hijos
        traverse(node, nv);
    }
};

int main(int argc, char* argv[])
{
    // Check command-line parameters
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <model file>\n";
        exit(1);
    }

    // Load the model
    osg::ref_ptr<osg::Node> loadedModel = osgDB::readNodeFile(argv[1]);
    if (!loadedModel)
    {
        std::cerr << "Problem opening '" << argv[1] << "'\n";
        exit(1);
    }

    osg::ref_ptr<osg::Group> root (new osg::Group());

    auto transform = new osg::PositionAttitudeTransform;
    transform->addChild(loadedModel);
    transform->setUpdateCallback(new SpinCallback);

    auto transform2 = new osg::PositionAttitudeTransform;
    transform2->addChild(loadedModel);
    transform2->setPosition(osg::Vec3(2.0, 0.0, 0.0));
    transform2->setUpdateCallback(new SpinCallback);

    root->addChild(transform);
    root->addChild(transform2);

    // Create a viewer and set the scene data to the root node
    osgViewer::Viewer viewer;
    viewer.setSceneData(root);

    // Set a trackball manipulator for user interaction with the view
    viewer.setCameraManipulator(new osgGA::TrackballManipulator);

    // Enter the main rendering loop
    viewer.run();
}
