#include "libs.hpp"
#include "voxel.hpp"

static const float world::voxel::SCALE=1;

static const unsigned int world::voxel::ATLAS_WIDTH=16;
static const unsigned int world::voxel::ATLAS_SCALE=32;

world::voxel::voxel():
  present(common::signals::NO),
  type(VOX_GRASS)
{

}

world::voxel::voxel(world::voxel::presence g_present, world::voxel_type g_type):
  present(g_present),
  type(g_type)
{

}

void world::voxel::presence_set(world::voxel::presence g_present)
{
  present=g_present;
}

void world::voxel::type_set(world::voxel_type g_type)
{
  type=g_type;
}

void world::voxel::mesh_generate(world::mesh_part* given, world::voxel::faces g_faces, math::vector<float, 3> offset, unsigned int index)
{
  if(g_faces.north==common::signals::YES){
    corners face=
      {
	(offset+math::vector<float, 3>({1, 1, 1}))*SCALE,
	(offset+math::vector<float, 3>({-1, 1, 1}))*SCALE,
	(offset+math::vector<float, 3>({1, -1, 1}))*SCALE,
	(offset+math::vector<float, 3>({-1, -1, 1}))*SCALE
      };
    
    generate_face(given,face,index);
    index+=4;
  }

  if(g_faces.south==common::signals::YES){
    corners face=
      {
	(offset+math::vector<float, 3>({-1, 1, -1}))*SCALE,
	(offset+math::vector<float, 3>({1, 1, -1}))*SCALE,
	(offset+math::vector<float, 3>({-1, -1, -1}))*SCALE,
	(offset+math::vector<float, 3>({1, -1, -1}))*SCALE
      };

    generate_face(given,face,index);
    index+=4;
  }

  if(g_faces.east==common::signals::YES){
    corners face=
      {
	(offset+math::vector<float, 3>({1, 1, -1}))*SCALE,
	(offset+math::vector<float, 3>({1, 1, 1}))*SCALE,
	(offset+math::vector<float, 3>({1, -1, -1}))*SCALE,
	(offset+math::vector<float, 3>({1, -1, 1}))*SCALE
      };

    generate_face(given,face,index);
    index+=4;
  }

  if(g_faces.west==common::signals::YES){
    corners face=
      {
	(offset+math::vector<float, 3>({-1, 1, 1}))*SCALE,
	(offset+math::vector<float, 3>({-1, 1, -1}))*SCALE,
	(offset+math::vector<float, 3>({-1, -1, 1}))*SCALE,
	(offset+math::vector<float, 3>({-1, -1, -1}))*SCALE
      };

    generate_face(given,face,index);
    index+=4;
  }

  if(g_faces.up==common::signals::YES){
    corners face=
      {
	(offset+math::vector<float, 3>({-1, 1, 1}))*SCALE,
	(offset+math::vector<float, 3>({1, 1, 1}))*SCALE,
	(offset+math::vector<float, 3>({-1, 1, -1}))*SCALE,
	(offset+math::vector<float, 3>({1, 1, -1}))*SCALE
      };

    generate_face(given,face,index);
    index+=4;
  }

  if(g_faces.down==common::signals::YES){
    corners face=
      {
	(offset+math::vector<float, 3>({-1, -1, -1}))*SCALE,
	(offset+math::vector<float, 3>({1, -1, -1}))*SCALE,
	(offset+math::vector<float, 3>({-1, -1, 1}))*SCALE,
	(offset+math::vector<float, 3>({1, -1, 1}))*SCALE
      };

    generate_face(given,face,index);
    index+=4;
  }
}

world::voxel::presence world::voxel::presence_get()
{
  return present;
}

world::voxel_type world::voxel::type_get()
{
  return type;
}

void world::voxel::generate_face(world::mesh_part* g_mesh, world::voxel::corners g_corners, unsigned int offset)
{
  float unit=1/(float)ATLAS_WIDTH;
  
  float texture_offset_y=1-(1+((int)type)/ATLAS_WIDTH)*unit;
  float texture_offset_x=(((int)type)%ATLAS_WIDTH)*unit;

  g_mesh->indices.push_back(offset);
  g_mesh->indices.push_back(offset+1);
  g_mesh->indices.push_back(offset+2);

  g_mesh->indices.push_back(offset);
  g_mesh->indices.push_back(offset+2);
  g_mesh->indices.push_back(offset+3);

  push_vector(g_mesh, g_corners.iii);
  g_mesh->vertices.push_back(texture_offset_x+0);
  g_mesh->vertices.push_back(texture_offset_y+0);

  push_vector(g_mesh, g_corners.i);
  g_mesh->vertices.push_back(texture_offset_x+0);
  g_mesh->vertices.push_back(texture_offset_y+unit);

  push_vector(g_mesh, g_corners.ii);
  g_mesh->vertices.push_back(texture_offset_x+unit);
  g_mesh->vertices.push_back(texture_offset_y+unit);

  push_vector(g_mesh, g_corners.iv);
  g_mesh->vertices.push_back(texture_offset_x+unit);
  g_mesh->vertices.push_back(texture_offset_y+0);
}

void world::voxel::push_vector(world::mesh_part* g_mesh, math::vector<float, 3> v)
{
  g_mesh->vertices.push_back(v[0]);
  g_mesh->vertices.push_back(v[1]);
  g_mesh->vertices.push_back(v[2]);
}

bool world::voxel::covering(world::voxel_type g_type)
{
  return ((present==common::signals::YES &&
	   (transparent()==common::signals::YES ? type==g_type : true))
	  ? common::signals::YES
	  : common::signals::NO);
}

bool world::voxel::transparent()
{
  if(type==VOX_WAWA || type==VOX_UNI){
    return common::signals::YES;
  }

  return common::signals::NO;
}
