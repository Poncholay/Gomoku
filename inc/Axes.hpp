//
// Axis.hpp for indieStudio in /home/wilmot_g/Rendu/cpp_indie_studio/LeHaineux
//
// Made by guillaume wilmot
// Login   <wilmot_g@epitech.net>
//
// Started on  Thu Apr 28 15:54:52 2016 guillaume wilmot
// Last update Tue May 24 16:29:11 2016 guillaume wilmot
//

class AxesSceneNode : public irr::scene::ISceneNode
{
  irr::scene::SMeshBuffer	ZMeshBuffer;
  irr::scene::SMeshBuffer	YMeshBuffer;
  irr::scene::SMeshBuffer	XMeshBuffer;
  irr::video::SColor		ZColor;
  irr::video::SColor		YColor;
  irr::video::SColor		XColor;

public:
  AxesSceneNode(irr::scene::ISceneNode *parent, irr::scene::ISceneManager *mgr, irr::s32 id) : ISceneNode(parent, mgr, id)
  {

#ifdef _DEBUG
    setDebugName("AxesSceneNode");
#endif

    irr::u16	u[36] = {0, 2, 1, 0, 3, 2, 1, 5, 4, 1, 2, 5, 4, 6, 7, 4, 5, 6, 7, 3, 0, 7, 6, 3, 3, 5, 2, 3, 6, 5, 0, 1, 4, 0, 4, 7};

    ZMeshBuffer.Indices.set_used(36);
    YMeshBuffer.Indices.set_used(36);
    XMeshBuffer.Indices.set_used(36);
    // Color Settings
    ZColor = irr::video::SColor(255, 0, 0, 255);
    YColor = irr::video::SColor(255, 0, 255, 0);
    XColor = irr::video::SColor(255, 255, 0, 0);
    for (irr::s32 i = 0; i < 36; ++i)
      {
	ZMeshBuffer.Indices[i] = u[i];
	YMeshBuffer.Indices[i] = u[i];
	XMeshBuffer.Indices[i] = u[i];
      }
    // Default Position, Rotation and Scale
    this->setPosition(irr::core::vector3df(0, 0, 0));
    this->setRotation(irr::core::vector3df(0, 0, 0));
    this->setScale(irr::core::vector3df(10, 10, 10));
    // Axes Box Coordinates Settings
    setAxesCoordinates();
  }

  virtual ~AxesSceneNode(){}

  virtual void OnRegisterSceneNode()
  {
    if (!IsVisible)
      return ;
    SceneManager->registerNodeForRendering(this);
    ISceneNode::OnRegisterSceneNode();
  }

  virtual void render()
  {
    irr::video::IVideoDriver	*driver = SceneManager->getVideoDriver();
    driver->setMaterial(ZMeshBuffer.Material);
    driver->setTransform(irr::video::ETS_WORLD, AbsoluteTransformation);
    driver->drawMeshBuffer(&ZMeshBuffer);

    driver->setMaterial(YMeshBuffer.Material);
    driver->setTransform(irr::video::ETS_WORLD, AbsoluteTransformation);
    driver->drawMeshBuffer(&YMeshBuffer);

    driver->setMaterial(XMeshBuffer.Material);
    driver->setTransform(irr::video::ETS_WORLD, AbsoluteTransformation);
    driver->drawMeshBuffer(&XMeshBuffer);
  }

  void setAxesCoordinates()
  {
    ZMeshBuffer.Vertices.set_used(8);
    ZMeshBuffer.Material.Wireframe = false;
    ZMeshBuffer.Material.Lighting = false;
    ZMeshBuffer.Vertices[0]  = irr::video::S3DVertex(-0.25, -0.25, 0, -1, -1, -1, ZColor, 0, 1);
    ZMeshBuffer.Vertices[1]  = irr::video::S3DVertex(0.25, -0.25, 0,  1, -1, -1, ZColor, 1, 1);
    ZMeshBuffer.Vertices[2]  = irr::video::S3DVertex(0.25, 0.25, 0,  1, 1, -1, ZColor, 1, 0);
    ZMeshBuffer.Vertices[3]  = irr::video::S3DVertex(-0.25, 0.25, 0, -1, 1, -1, ZColor, 0, 0);
    ZMeshBuffer.Vertices[4]  = irr::video::S3DVertex(0.25, -0.25, 25,  1, -1, 1, ZColor, 0, 1);
    ZMeshBuffer.Vertices[5]  = irr::video::S3DVertex(0.25, 0.25, 25,  1, 1, 1, ZColor, 0, 0);
    ZMeshBuffer.Vertices[6]  = irr::video::S3DVertex(-0.25, 0.25, 25, -1, 1, 1, ZColor, 1, 0);
    ZMeshBuffer.Vertices[7]  = irr::video::S3DVertex(-0.25, -0.25, 25, -1,-1, 1, ZColor, 1, 1);
    ZMeshBuffer.BoundingBox.reset(0, 0, 0);

    YMeshBuffer.Vertices.set_used(8);
    YMeshBuffer.Material.Wireframe = false;
    YMeshBuffer.Material.Lighting = false;
    YMeshBuffer.Vertices[0]  = irr::video::S3DVertex(-0.25, 0, 0.25, -1, -1, -1, YColor, 0, 1);
    YMeshBuffer.Vertices[1]  = irr::video::S3DVertex(0.25, 0, 0.25,  1, -1, -1, YColor, 1, 1);
    YMeshBuffer.Vertices[2]  = irr::video::S3DVertex(0.25, 0, -0.25,  1, 1, -1, YColor, 1, 0);
    YMeshBuffer.Vertices[3]  = irr::video::S3DVertex(-0.25, 0, -0.25, -1, 1,-1, YColor, 0, 0);
    YMeshBuffer.Vertices[4]  = irr::video::S3DVertex(0.25, 25, 0.25,  1, -1, 1, YColor, 0, 1);
    YMeshBuffer.Vertices[5]  = irr::video::S3DVertex(0.25, 25, -0.25,  1, 1, 1, YColor, 0, 0);
    YMeshBuffer.Vertices[6]  = irr::video::S3DVertex(-0.25, 25, -0.25, -1, 1, 1, YColor, 1, 0);
    YMeshBuffer.Vertices[7]  = irr::video::S3DVertex(-0.25, 25, 0.25, -1, -1, 1, YColor, 1, 1);
    YMeshBuffer.BoundingBox.reset(0, 0, 0);

    XMeshBuffer.Vertices.set_used(8);
    XMeshBuffer.Material.Wireframe = false;
    XMeshBuffer.Material.Lighting = false;
    XMeshBuffer.Vertices[0]  = irr::video::S3DVertex(0, -0.25 ,0.25, -1, -1, -1, XColor, 0, 1);
    XMeshBuffer.Vertices[1]  = irr::video::S3DVertex(0, -0.25, -0.25, 1, -1, -1, XColor, 1, 1);
    XMeshBuffer.Vertices[2]  = irr::video::S3DVertex(0, 0.25, -0.25, 1, 1, -1, XColor, 1, 0);
    XMeshBuffer.Vertices[3]  = irr::video::S3DVertex(0, 0.25, 0.25, -1, 1, -1, XColor, 0, 0);
    XMeshBuffer.Vertices[4]  = irr::video::S3DVertex(25, -0.25, -0.25, 1,-1, 1, XColor, 0, 1);
    XMeshBuffer.Vertices[5]  = irr::video::S3DVertex(25, 0.25, -0.25, 1, 1, 1, XColor, 0, 0);
    XMeshBuffer.Vertices[6]  = irr::video::S3DVertex(25, 0.25, 0.25, -1, 1, 1, XColor, 1, 0);
    XMeshBuffer.Vertices[7]  = irr::video::S3DVertex(25, -0.25, 0.25, -1,-1, 1, XColor, 1, 1);
    XMeshBuffer.BoundingBox.reset(0, 0, 0);
  }

  virtual const irr::core::aabbox3d<irr::f32> &getBoundingBox() const {return (ZMeshBuffer.BoundingBox);}

  void setAxesScale(irr::f32 scale)
  {
    ZMeshBuffer.Vertices.set_used(8);
    ZMeshBuffer.Material.Wireframe = false;
    ZMeshBuffer.Material.Lighting = false;
    ZMeshBuffer.Vertices[0]  = irr::video::S3DVertex(-0.25, -0.25, 0, -1, -1, -1, ZColor, 0, 1);
    ZMeshBuffer.Vertices[1]  = irr::video::S3DVertex(0.25, -0.25, 0, 1, -1, -1, ZColor, 1, 1);
    ZMeshBuffer.Vertices[2]  = irr::video::S3DVertex(0.25, 0.25, 0, 1, 1, -1, ZColor, 1, 0);
    ZMeshBuffer.Vertices[3]  = irr::video::S3DVertex(-0.25, 0.25, 0, -1, 1, -1, ZColor, 0, 0);
    ZMeshBuffer.Vertices[4]  = irr::video::S3DVertex(0.25, -0.25, scale, 1, -1, 1, ZColor, 0, 1);
    ZMeshBuffer.Vertices[5]  = irr::video::S3DVertex(0.25, 0.25, scale, 1, 1, 1, ZColor, 0, 0);
    ZMeshBuffer.Vertices[6]  = irr::video::S3DVertex(-0.25, 0.25, scale, -1, 1, 1, ZColor, 1, 0);
    ZMeshBuffer.Vertices[7]  = irr::video::S3DVertex(-0.25, -0.25, scale, -1, -1, 1, ZColor, 1, 1);
    ZMeshBuffer.BoundingBox.reset(0, 0, 0);

    YMeshBuffer.Vertices.set_used(8);
    YMeshBuffer.Material.Wireframe = false;
    YMeshBuffer.Material.Lighting = false;
    YMeshBuffer.Vertices[0]  = irr::video::S3DVertex(-0.25, 0, 0.25, -1, -1, -1, YColor, 0, 1);
    YMeshBuffer.Vertices[1]  = irr::video::S3DVertex(0.25, 0, 0.25, 1, -1, -1, YColor, 1, 1);
    YMeshBuffer.Vertices[2]  = irr::video::S3DVertex(0.25, 0, -0.25, 1, 1, -1, YColor, 1, 0);
    YMeshBuffer.Vertices[3]  = irr::video::S3DVertex(-0.25, 0, -0.25, -1, 1, -1, YColor, 0, 0);
    YMeshBuffer.Vertices[4]  = irr::video::S3DVertex(0.25, scale, 0.25, 1, -1, 1, YColor, 0, 1);
    YMeshBuffer.Vertices[5]  = irr::video::S3DVertex(0.25, scale, -0.25, 1, 1, 1, YColor, 0, 0);
    YMeshBuffer.Vertices[6]  = irr::video::S3DVertex(-0.25, scale, -0.25, -1, 1, 1, YColor, 1, 0);
    YMeshBuffer.Vertices[7]  = irr::video::S3DVertex(-0.25, scale, 0.25, -1, -1, 1, YColor, 1, 1);
    YMeshBuffer.BoundingBox.reset(0, 0, 0);

    XMeshBuffer.Vertices.set_used(8);
    XMeshBuffer.Material.Wireframe = false;
    XMeshBuffer.Material.Lighting = false;
    XMeshBuffer.Vertices[0]  = irr::video::S3DVertex(0, -0.25, 0.25, -1, -1, -1, XColor, 0, 1);
    XMeshBuffer.Vertices[1]  = irr::video::S3DVertex(0, -0.25, -0.25, 1, -1, -1, XColor, 1, 1);
    XMeshBuffer.Vertices[2]  = irr::video::S3DVertex(0, 0.25, -0.25, 1, 1, -1, XColor, 1, 0);
    XMeshBuffer.Vertices[3]  = irr::video::S3DVertex(0, 0.25, 0.25, -1, 1, -1, XColor, 0, 0);
    XMeshBuffer.Vertices[4]  = irr::video::S3DVertex(scale, -0.25, -0.25, 1, -1, 1, XColor, 0, 1);
    XMeshBuffer.Vertices[5]  = irr::video::S3DVertex(scale, 0.25, -0.25, 1, 1, 1, XColor, 0, 0);
    XMeshBuffer.Vertices[6]  = irr::video::S3DVertex(scale, 0.25, 0.25, -1, 1, 1, XColor, 1, 0);
    XMeshBuffer.Vertices[7]  = irr::video::S3DVertex(scale, -0.25, 0.25, -1, -1, 1, XColor, 1, 1);
    XMeshBuffer.BoundingBox.reset(0, 0, 0);
  }
};
