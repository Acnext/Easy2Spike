import visii
import v2s
opt = lambda: None
opt.spp = 32
opt.width = 400
opt.height = 250
opt.noise = False
opt.path_obj = 'resources/pku2.obj'
opt.path_obj2 = "resources/models/teapot/teapot.obj"
opt.path_obj3 = "resources/models/sphere/sphere.obj"
opt.out = 'out'

# # # # # # # # # # # # # # # # # # # # # # # # #
visii.initialize(headless=True, verbose=True)

if not opt.noise is True: 
    visii.enable_denoiser()

camera = visii.entity.create(
    name = "camera",
    transform = visii.transform.create("camera"),
    camera = visii.camera.create(
        name = "camera",  
        aspect = float(opt.width)/float(opt.height)
    )
)

camera.get_transform().look_at(
    at = (0,0,0),
    up = (0,0,1),
    eye = (0,3.0,0.2),
)
visii.set_camera_entity(camera)

visii.set_dome_light_sky(sun_position = (10, 10, 1), saturation = 2)
visii.set_dome_light_intensity(1.5)

# # # # # # # # # # # # # # # # # # # # # # # # #

floor = visii.entity.create(
    name = "floor",
    mesh = visii.mesh.create_plane("floor", size = (10,10)),
    material = visii.material.create("floor", base_color = (.5, .5, .5), roughness = 0.0, metallic = 1.0),
    transform = visii.transform.create("floor", position = (0,0,-.3))
)

# Next, let's load an obj
mesh = visii.mesh.create_from_file("obj", opt.path_obj)
mesh2 = visii.mesh.create_from_file("obj2", opt.path_obj2)
mesh3 =  visii.mesh.create_from_file("obj3", opt.path_obj3)
# Now, lets make three instances of that mesh
obj1 = visii.entity.create(
    name="obj1",
    mesh = mesh,
    transform = visii.transform.create("obj1"),
    material = visii.material.create("obj1")
)
"""
obj2 = visii.entity.create(
    name="obj2",
    mesh = mesh2,
    transform = visii.transform.create("obj2"),
    material = visii.material.create("obj2")
)
obj3 = visii.entity.create(
    name="obj3",
    mesh = mesh3,
    transform = visii.transform.create("obj3"),
    material = visii.material.create("obj3")
)
# place those objects into the scene

# lets set the obj_entity up

obj2.get_transform().set_position((0, -2, 0.6))
obj2.get_transform().set_rotation((1, 0, 0, 1))
obj2.get_transform().set_scale((0.5, 0.5, 0.5)) #茶壶使用
obj2.get_material().set_base_color((1,0,0))  
obj2.get_material().set_roughness(0.7)   
obj2.get_material().set_specular(1)   
obj2.get_material().set_sheen(1)

obj3.get_transform().set_position((2, -2, 0.6))
obj3.get_transform().set_rotation((1, 0, 0, 1))
obj3.get_transform().set_scale((0.5, 0.5, 0.5)) #茶壶使用
obj3.get_material().set_base_color((1,0,0))  
obj3.get_material().set_roughness(0.7)   
obj3.get_material().set_specular(1)   
obj3.get_material().set_sheen(1)
"""
obj1.get_transform().set_position((0, -2, 0.6))#多物体的时候-2 -2 0.6
obj1.get_transform().set_rotation((1, 0, 0, 1))
obj1.get_transform().set_scale((5, 5, 5)) #pku使用555
obj1.get_material().set_base_color((1,0,0))  
obj1.get_material().set_roughness(0.7)   
obj1.get_material().set_specular(1)   
obj1.get_material().set_sheen(1)
# # # # # # # # # # # # # # # # # # # # # # # # #
tot = 100
for i in range(tot):
  obj1.get_transform().set_rotation((0, 1, 0, 0.01 * i))
  #obj2.get_transform().set_rotation((0, 1, 0, 0.01 * i))
  #obj3.get_transform().set_rotation((0, 1, 0, 0.01 * i))
  visii.render_to_png(
    width=int(opt.width), 
    height=int(opt.height), 
    samples_per_pixel=int(opt.spp),
    image_path="out/"+str(i).zfill(5)+".png"
  )
# let's clean up the GPU
visii.deinitialize()
v2s.get_spike(w = opt.width, h = opt.height, frame_tot = tot)