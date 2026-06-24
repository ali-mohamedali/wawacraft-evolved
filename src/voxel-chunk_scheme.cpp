#include "libs.hpp"
#include "voxel.hpp"

world::chunk_scheme::chunk_scheme(file::image_loader* g_atlas):
  atlas(g_atlas),
  atlas_texture(g_atlas),
  noise_map(640)
{
  chunks.push_back(world::chunk(math::vector<float, 3>({0, 0, 0}), noise_map));
  origin=0;

  for(int x=0; x<RENDER_LIST_SIZE; x++){
    render_list[x]=-1;
  }
}

world::voxel& world::chunk_scheme::raycast(math::vector<float, 3> position, math::vector<float, 3> orientation, bool over)
{
  world::chunk& current_chunk=chunks[chunk_create(position)];
  
  math::vector<float, 3> chunk_position=conversion_cycle(position);
  position=(position-chunk_position)*(1/(world::voxel::SCALE*2.0));
  math::vector<float, 3> index_position({std::floor(position[0]), std::floor(position[1]), std::floor(position[2])});
  math::vector<float, 3> nposition=position;
  
  math::vector<float, 3> step;
  for(int i=0; i<3; i++){step[i]=(orientation[i]>0 ? 1 : (orientation[i]==0 ? 0 : -1));}

  math::vector<float, 3> delta;
  for(int i=0; i<3; i++){delta[i]=1/orientation[i];}
  
  math::vector<float, 3> bound;
  for(int i=0; i<3; i++){
    bound[i]=(position[i]-(index_position[i]+(step[i]>0 ? step[i] : 0)))/orientation[i];
  }
  
  int steps=0;
  int least=0;
  while(current_chunk.voxel_get(index_position[0], index_position[2], index_position[1]).presence_get()==common::signals::NO){
    if(++steps>world::chunk::SIZE){
      index_position=math::vector<float, 3>({std::floor(position[0]), std::floor(position[1]), std::floor(position[2])});
      break;
      
    }
    
    for(int i=0; i<3; i++){
      if(abs(bound[i])<=abs(bound[least])){
	least=i;
      }
    }
    
    bound[least]+=delta[least];
    index_position[least]+=step[least];
    nposition[least]+=step[least];
    
    if(index_position[least]>=world::chunk::SIZE || index_position[least]<0){
      math::vector<float, 3> nindex_position=index_position;
      nindex_position[least]=((int)std::floor(nposition[least])%world::chunk::SIZE);
      if(nindex_position[least]<0){nindex_position[least]+=world::chunk::SIZE;}

      if(over==common::signals::YES
	 && chunks[chunk_create(nposition*(world::voxel::SCALE*2.0)+chunk_position)].voxel_get((unsigned int)nindex_position[0], (unsigned int)nindex_position[2], (unsigned int)nindex_position[1]).presence_get()==common::signals::YES){
	for(int i=0; i<RENDER_LIST_SIZE; i++){
	  chunk_load(render_list[i]);
	}
	
	index_position[least]-=step[least];
	nposition[least]-=step[least];

	world::voxel& v=current_chunk.data[(unsigned int)nposition[0]][(unsigned int)nposition[2]][(unsigned int)nposition[1]];

	world::voxel_type vt=v.type_get();
  
	world::mesh_part temp;

	world::voxel::faces f=
	  {
	    common::signals::YES,
	    common::signals::YES,
	    common::signals::YES,
	    common::signals::YES,
	    common::signals::YES,
	    common::signals::YES
	  };

	v.type_set(VOX_NONE);
	v.mesh_generate(&temp, f, index_position*2, 0);
	v.type_set(vt);
  
	block_cursor.set(temp.vertices, temp.indices);
	block_cursor.model_set(math::matrix_model(chunk_position, math::quat<float>({1,0,0,0}), 1));
	
	return v;
      }
      
      return raycast((nposition*(world::voxel::SCALE*2.0))+chunk_position, orientation, over);
    }
  }

  if(over==common::signals::YES){
    index_position[least]-=step[least];
    nposition[least]-=step[least];
  }

  world::voxel& v=current_chunk.data[(unsigned int)nposition[0]][(unsigned int)nposition[2]][(unsigned int)nposition[1]];
  world::voxel_type vt=v.type_get();
  
  world::mesh_part temp;

  world::voxel::faces f=
    {
      common::signals::YES,
      common::signals::YES,
      common::signals::YES,
      common::signals::YES,
      common::signals::YES,
      common::signals::YES
    };

  v.type_set(VOX_NONE);
  v.mesh_generate(&temp, f, index_position*2, 0);
  v.type_set(vt);
  
  block_cursor.set(temp.vertices, temp.indices);
  block_cursor.model_set(math::matrix_model(chunk_position, math::quat<float>({1,0,0,0}), 1));

  return v;
}

void world::chunk_scheme::render(math::vector<float, 3> g_position, bool depth)
{
  render_list_update(g_position);
  
  for(int x=0; x<RENDER_LIST_SIZE; x++){
    if(render_list[x]>=0){
      chunk_render(render_list[x]);
    }
  }
  
  block_cursor.render(&atlas_texture);
}

unsigned int world::chunk_scheme::chunk_create(math::vector<float, 3> g_position)
{
  int c=chunk_search(g_position);
  if(c<0){
    chunks.push_back(world::chunk(conversion_cycle(g_position), noise_map));
    return chunks.size()-1;
  }
  
  return c;
}

void world::chunk_scheme::chunk_render(unsigned int given)
{
  chunks[given].mesh.render(&atlas_texture);
}

void world::chunk_scheme::chunk_load(unsigned int given)
{
  chunks[given].mesh_generate(*this);
}

void world::chunk_scheme::chunk_unload(unsigned int given)
{
  if(given){
    chunks[given].mesh_wipe();
  }
}

void world::chunk_scheme::render_list_add(unsigned int given)
{
  for(int x=0; x<RENDER_LIST_SIZE; x++){
    if(render_list[x]==given){
      return;
    }else if(render_list[x]<0){
      render_list[x]=given;
      chunk_load(given);
      
      return;
    }
  }
}

void world::chunk_scheme::render_list_remove(unsigned int given)
{
  for(int x=0; x<RENDER_LIST_SIZE; x++){
    if(render_list[x]==given){
      render_list[x]=-1;
      chunk_unload(given);
      
      return;
    }
  }
}

void world::chunk_scheme::unload_all()
{
  for(int i=0; i<chunks.size(); i++){
    chunk_unload(i);
  }
}

int world::chunk_scheme::chunk_search(math::vector<float, 3> g_position)
{
  g_position=conversion_cycle(g_position);
  
  for(int i=0; i<chunks.size(); i++){
    if(chunks[i].position_get()==g_position){
      return i;
    }
  }

  return -1;
}

void world::chunk_scheme::render_list_update(math::vector<float, 3> g_position)
{
  for(int i=0; i<RENDER_LIST_SIZE; i++){
    if(render_list[i]<0){
      continue;
    }

    math::vector<float, 3> diff=chunks[render_list[i]].position_get()-g_position;
    for(int j=0; j<3; j++){
      if(!(diff[j]>=-1 && diff[j]<=1)){
	render_list[i]=-1;
	chunk_unload(i);

	break;
      }
    }
  }

  for(int j=-1; j<2; j++){
    for(int k=-1; k<2; k++){
      for(int i=-1; i<2; i++){
	render_list_add(chunk_create(g_position+chunk_world_convert(math::vector<float, 3>({i, j, k}))));
      }
    }
  }
}

math::vector<float, 3> world::chunk_scheme::world_chunk_convert(math::vector<float, 3> g_position)
{
  for(int x=0; x<3; x++){
    g_position[x]=std::floor(g_position[x]/(world::chunk::SIZE*world::voxel::SCALE*2));
  }

  return g_position;
}

math::vector<float, 3> world::chunk_scheme::chunk_world_convert(math::vector<float, 3> g_position)
{
  return g_position*world::chunk::SIZE*world::voxel::SCALE*2;
}

math::vector<float, 3> world::chunk_scheme::conversion_cycle(math::vector<float, 3> g_position)
{
  return chunk_world_convert(world_chunk_convert(g_position));
}
