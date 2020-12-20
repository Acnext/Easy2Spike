import visii
import v2s
opt = lambda: None
opt.spp = 32
opt.width = 400
opt.height = 250
opt.noise = False
opt.path_obj = 'content/bmw/bmw.obj'
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
#mesh2 = visii.mesh.create_from_file("obj", opt.path_obj2)
# Now, lets make three instances of that mesh
obj1 = visii.entity.create(
    name="obj1",
    mesh = mesh,
    transform = visii.transform.create("obj1"),
    material = visii.material.create("obj1")
)

# place those objects into the scene

# lets set the obj_entity up
obj1.get_transform().set_position((0, 0, 0))
obj1.get_transform().set_rotation((1, 0, 0, 1))
obj1.get_transform().set_scale((0.005, 0.005, 0.005))
tot = 100
# # # # # # # # # # # # # # # # # # # # # # # # #
for i in range(tot):
  obj1.get_transform().set_position((3 - i * 0.04, 0, 0))
  visii.render_to_png(
    width=int(opt.width), 
    height=int(opt.height), 
    samples_per_pixel=int(opt.spp),
    image_path="out/"+str(i).zfill(5)+".png"
  )
  

# let's clean up the GPU


visii.deinitialize()
v2s.get_spike(w = opt.width, h = opt.height, frame_tot = tot)