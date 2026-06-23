#ifndef VOXEL_H
#define VOXEL_H

#include "libs.hpp"
#include "common.hpp"
#include "vector.hpp"
#include "mesh.hpp"
#include "file.hpp"
#include "noise.hpp"

namespace world{
  enum voxel_type{
    VOX_NONE=0,
    VOX_GRASS=1,
    VOX_MUD=2,
    VOX_WOOD=3,
    VOX_STONE=4,
    VOX_WAWA=5,
    VOX_UNI=6
  };

  struct mesh_part{
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
  };
  
  class voxel{
  public:
    typedef bool presence;
    
    typedef std::vector<float> vertices;
    typedef std::vector<unsigned int> indices;

    struct faces{
      bool north=common::signals::NO;
      bool south=common::signals::NO;
      bool east=common::signals::NO;
      bool west=common::signals::NO;
      bool up=common::signals::NO;
      bool down=common::signals::NO;
    };

    struct corners{
      math::vector<float, 3> i;
      math::vector<float, 3> ii;
      math::vector<float, 3> iii;
      math::vector<float, 3> iv;
    };
    
    static const float SCALE;
    
    static const unsigned int ATLAS_WIDTH;
    static const unsigned int ATLAS_SCALE;
    
    voxel();
    voxel(presence, voxel_type);
    
    void presence_set(presence);
    void type_set(voxel_type);

    void mesh_generate(mesh_part*, voxel::faces, math::vector<float, 3>, unsigned int index);
    
    presence presence_get();

    voxel_type type_get();

    bool covering(voxel_type);
    bool transparent();
    
  private:
    void generate_face(mesh_part*, corners, unsigned int);
    void push_vector(mesh_part*, math::vector<float, 3>);
    
    presence present;
    voxel_type type;
  };

  class chunk_scheme;
  
  class chunk{
  public:
    static const unsigned int SIZE=32;

    chunk(math::vector<float, 3>, math::noise_2d&);
    
    void position_set(math::vector<float, 3>);
    void voxel_set(unsigned int, unsigned int, unsigned int, voxel::presence, voxel_type);
    
    void mesh_generate(chunk_scheme&);
    void mesh_wipe();

    voxel voxel_get(unsigned int, unsigned int, unsigned int);
    
    math::vector<float, 3> position_get();

    graphics::textured_mesh mesh;
    
  protected:
    math::vector<float, 3> position;

    voxel data[SIZE][SIZE][SIZE];

    friend class chunk_scheme;
  };

  class chunk_scheme{
  public:
    chunk_scheme(file::image_loader*);
    
    void render(math::vector<float, 3>, bool=common::signals::YES);

    world::voxel& raycast(math::vector<float, 3>, math::vector<float, 3>, bool=common::signals::NO);
    
  private:
    static const unsigned int RENDER_LIST_SIZE=27;
    
    chunk_scheme();
    
    void chunk_render(unsigned int);

    void chunk_load(unsigned int);
    void chunk_unload(unsigned int);

    void render_list_update(math::vector<float, 3>);
    void render_list_add(unsigned int);
    void render_list_remove(unsigned int);
    
    void unload_all();
    
    math::vector<float, 3> world_chunk_convert(math::vector<float, 3>);
    math::vector<float, 3> chunk_world_convert(math::vector<float, 3>);

    math::vector<float, 3> conversion_cycle(math::vector<float, 3>);
    
    unsigned int chunk_create(math::vector<float, 3>);
    int chunk_search(math::vector<float, 3>);
    
    unsigned int origin;

    math::noise_2d noise_map;
    
    file::image_loader* atlas;
    graphics::texture atlas_texture;

    graphics::textured_mesh block_cursor;
    
    std::vector<chunk> chunks;

    int render_list[RENDER_LIST_SIZE];

    friend world::chunk;
  };
}

#endif
