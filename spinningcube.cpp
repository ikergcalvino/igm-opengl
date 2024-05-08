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
        osg::PositionAttitudeTransform *pat = dynamic_cast<osg::PositionAttitudeTransform *>(node);

        if (pat)
        {
            double time = nv->getFrameStamp()->getSimulationTime();

            double angleX = osg::inDegrees(time * 40.0);
            double angleY = osg::inDegrees(time * 30.0);
            double angleZ = osg::inDegrees(time * 20.0);

            osg::Quat rotationX(angleX, osg::Vec3(1, 0, 0));
            osg::Quat rotationY(angleY, osg::Vec3(0, 1, 0));
            osg::Quat rotationZ(angleZ, osg::Vec3(0, 0, 1));

            osg::Quat finalRotation = rotationY * rotationX * rotationZ;

            pat->setAttitude(finalRotation);
        }

        traverse(node, nv);
    }
};

int main(int argc, char *argv[])
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

    auto root = new osg::Group();

    auto lightSource = new osg::LightSource();
    lightSource->addChild(loadedModel);
    lightSource->getLight()->setLightNum(1);
    lightSource->getLight()->setPosition(osg::Vec4(5.0, 5.0, 5.0, 1.0));
    lightSource->getLight()->setDiffuse(osg::Vec4(1.0, 0.5, 1.0, 1.0));

    auto state = root->getOrCreateStateSet();
    state->setMode(GL_LIGHT1, osg::StateAttribute::ON);

    auto light = new osg::PositionAttitudeTransform;
    light->addChild(lightSource);
    light->setPosition(osg::Vec3(5.0, 0.0, 1.0));
    light->setScale(osg::Vec3(0.2, 0.2, 0.2));

    auto texture = new osg::Texture2D();
    auto image = osgDB::readImageFile("spinningcube.png");
    texture->setImage(image);

    auto cube1 = new osg::PositionAttitudeTransform;
    cube1->addChild(loadedModel);
    cube1->setUpdateCallback(new SpinCallback);

    auto state_cube1 = cube1->getOrCreateStateSet();
    state_cube1->setTextureAttributeAndModes(0, texture);

    auto cube2 = new osg::PositionAttitudeTransform;
    cube2->addChild(loadedModel);
    cube2->setPosition(osg::Vec3(2.0, 0.0, 0.0));
    cube2->setUpdateCallback(new SpinCallback);

    auto state_cube2 = cube2->getOrCreateStateSet();
    state_cube2->setTextureAttributeAndModes(0, texture);

    root->addChild(light);
    root->addChild(cube1);
    root->addChild(cube2);

    // Create a viewer and set the scene data to the root node
    osgViewer::Viewer viewer;
    viewer.setSceneData(root);

    // Set a trackball manipulator for user interaction with the view
    viewer.setCameraManipulator(new osgGA::TrackballManipulator);

    // Enter the main rendering loop
    viewer.run();
}
