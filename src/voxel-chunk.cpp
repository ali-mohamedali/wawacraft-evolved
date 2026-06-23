#include "libs.hpp"
#include "voxel.hpp"

world::chunk::chunk(math::vector<float, 3> g_position, math::noise_2d& noise_map):
  position(g_position)
{
  for(int j=0; j<SIZE; j++){
    for(int k=0; k<SIZE; k++){
      for(int i=0; i<SIZE; i++){
	int sample=((1-4*noise_map.sample(abs(i+position[0])/(float)SIZE, abs(j+position[2])/(float)SIZE))*SIZE);
	
	if(k<=sample-position[1]){
	  voxel_set(i, j, k, common::signals::YES, (k==sample-position[1] ? VOX_GRASS :((rand()%2)>0 ? VOX_MUD : VOX_STONE)));
	}
      } 
    }
  }
}

void world::chunk::position_set(math::vector<float, 3> g_position)
{
  position=g_position;
}

void world::chunk::voxel_set(unsigned int i, unsigned int j, unsigned int k, world::voxel::presence g_presence, world::voxel_type g_type)
{
  data[i][j][k].presence_set(g_presence);
  data[i][j][k].type_set(g_type);
}

void world::chunk::mesh_generate(world::chunk_scheme& g_world)
{
  world::mesh_part accumulate;

  int n=g_world.chunk_search(position+g_world.chunk_world_convert(math::vector<float, 3>({0,0,1})));
  int s=g_world.chunk_search(position+g_world.chunk_world_convert(math::vector<float, 3>({0,0,-1})));
  int e=g_world.chunk_search(position+g_world.chunk_world_convert(math::vector<float, 3>({1,0,0})));
  int w=g_world.chunk_search(position+g_world.chunk_world_convert(math::vector<float, 3>({-1,0,0})));
  int u=g_world.chunk_search(position+g_world.chunk_world_convert(math::vector<float, 3>({0, 1, 0})));
  int d=g_world.chunk_search(position+g_world.chunk_world_convert(math::vector<float, 3>({0, -1, 0})));
  
  world::chunk* north=(n>=0 ? &g_world.chunks[n] : NULL);
  world::chunk* south=(s>=0 ? &g_world.chunks[s] : NULL);
  world::chunk* east=(e>=0 ? &g_world.chunks[e] : NULL);
  world::chunk* west=(w>=0 ? &g_world.chunks[w] : NULL);
  world::chunk* up=(u>=0 ? &g_world.chunks[u] : NULL);
  world::chunk* down=(d>=0 ? &g_world.chunks[d] : NULL);
  
  for(int k=0; k<SIZE; k++){
    for(int j=0; j<SIZE; j++){
      for(int i=0; i<SIZE; i++){
        if(data[i][j][k].presence_get()==common::signals::YES){
	  world::voxel::faces faces;

	  if((k==SIZE-1
	      || data[i][j][k+1].covering(data[i][j][k].type_get())==common::signals::NO)
	     && ((k==SIZE-1 && up) ? up->voxel_get(i, j, 0).covering(data[i][j][k].type_get())==common::signals::NO : true)){
	    faces.up=common::signals::YES;
	  }

	  if((k==0
	      || data[i][j][k-1].covering(data[i][j][k].type_get())==common::signals::NO)
	     && ((k==0 && down) ? down->voxel_get(i, j, SIZE-1).covering(data[i][j][k].type_get())==common::signals::NO : true)){
	    faces.down=common::signals::YES;
	  }
	  
	  if((j==SIZE-1
	      || data[i][j+1][k].covering(data[i][j][k].type_get())==common::signals::NO)
	     && ((j==SIZE-1 && north) ? north->voxel_get(i, 0, k).covering(data[i][j][k].type_get())==common::signals::NO : true)){
	    faces.north=common::signals::YES;
	  }

	  if((j==0
	      || data[i][j-1][k].covering(data[i][j][k].type_get())==common::signals::NO)
	     && ((j==0 && south) ? south->voxel_get(i, SIZE-1, k).covering(data[i][j][k].type_get())==common::signals::NO : true)){
	    faces.south=common::signals::YES;
	  }

	  if((i==SIZE-1
	      || data[i+1][j][k].covering(data[i][j][k].type_get())==common::signals::NO)
	     && ((i==SIZE-1 && east) ? east->voxel_get(0, j, k).covering(data[i][j][k].type_get())==common::signals::NO : true)){
	    faces.east=common::signals::YES;
	  }

	  if((i==0
	      || data[i-1][j][k].covering(data[i][j][k].type_get())==common::signals::NO)
	     && ((i==0 && west) ? west->voxel_get(SIZE-1, j, k).presence_get()==common::signals::NO : true)){
	    faces.west=common::signals::YES;
	  }
	  
	  data[i][j][k].mesh_generate(&accumulate, faces, math::vector<float, 3>({i, k, j})*2, accumulate.vertices.size()/5);
	}
      }
    }
  }
  
  mesh.model_set(math::matrix_model(position*world::voxel::SCALE, math::quat<float>({cos(0),0,0,sin(0)}), world::voxel::SCALE));
  mesh.set(accumulate.vertices, accumulate.indices);
}

void world::chunk::mesh_wipe()
{
  mesh.wipe();
}

world::voxel world::chunk::voxel_get(unsigned int i, unsigned int j, unsigned int k)
{
  return data[i][j][k];
}

math::vector<float, 3> world::chunk::position_get()
{
  return position;
}
