#include "libs.hpp"
#include "obj.hpp"

file::obj_loader::obj_loader(std::string g_path):
  loader(g_path)
{
  load();
}

void file::obj_loader::load()
{
  logging::log pen("load", "file::obj_loader", "loading a file");
  
  std::string file=file_get();
  std::string piece;
  std::stringstream file_stream(file);

  while(std::getline(file_stream, piece)){
    std::stringstream words(piece);
    std::string word;

    int v=0;
    int vt=0;
    int f=0;

    while(std::getline(words, word, ' ')){
      if(word[0]=="#"){
	break;
      }if(word=="v"){
	vt=0;
	f=0;
	v=3;
	continue;
      }else if(word=="vt"){
	v=0;
	f=0;
	vt=2;
	continue;
      }else if(word=="f"){
	v=vt=0;
	f=3;
	continue;
      }
      
      if(v>0){
	vertex.push_back(std::stof(word));
	v--;
      }else if(vt>0){
	texture.push_back(std::stof(word));
	vt--;
      }else if(f>0){
	int i=0;
	std::string vnum;
	for(i; i<word.size(); i++){
	  if(word[i]=='/'){
	    break;
	  }
	  
	  vnum+=word[i];
	}

	std::string tnum;
        i++;
        for(i; i<word.size(); i++){
	  if(word[i]=='/'){
	    break;
	  }

	  tnum+=word[i];
	}

	std::cout << tnum << std::endl;
	
	vertices.push_back(vertex[((std::stoi(vnum)-1)*3)]);
	vertices.push_back(vertex[((std::stoi(vnum)-1)*3)+1]);
	vertices.push_back(vertex[((std::stoi(vnum)-1)*3)+2]);
	
	if(vnum.size()!=word.size()){
	  vertices.push_back(texture[((std::stoi(tnum)-1)*2)]);
	  vertices.push_back(texture[((std::stoi(tnum)-1)*2)+1]);
	}else{
	  vertices.push_back(0);
	  vertices.push_back(0);
	}

	int size=indices.size();
	indices.push_back(size);

	f--;
      }
    }
  }
}
