////////////////////////////////////////////////////////////////////////////////
// ExMesh.h
// Author   : Bastien BOURINEAU
// Start Date : January 21, 2012
////////////////////////////////////////////////////////////////////////////////
/*********************************************************************************
*                                        *
*   This program is free software; you can redistribute it and/or modify     *
*   it under the terms of the GNU Lesser General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or      *
*   (at your option) any later version.                      *
*                                        *
**********************************************************************************/
////////////////////////////////////////////////////////////////////////////////
// Port to 3D Studio Max - Modified original version
// Author	      : Doug Perkowski - OC3 Entertainment, Inc.
// From work of : Francesco Giordana
// Start Date   : December 10th, 2007
////////////////////////////////////////////////////////////////////////////////

#ifndef _ExMesh_H
#define _ExMesh_H

#include "ExPrerequisites.h"
#include "ExOgreConverter.h"
#include "ExSkeleton.h"
#include "ExBlendshape.h"
#include "paramList.h"


namespace EasyOgreExporter
{
  class ExFace
  {
  public:
		  //constructor
      ExFace()
      {
      };

      //destructor
		  ~ExFace()
      {
      };

      // vertice indices
      std::vector<int> vertices;
  };

  class ExVertex
  {
  public:
		  //constructor
      ExVertex()
      {
        iMaxId = -1;
        iNext = -1;
      };

		  //constructor
      ExVertex(int id)
      {
        iMaxId = id;
        iNext = -2;
      };
  	  
      //destructor
		  ~ExVertex()
      {
      }

      bool cmpPointList(std::vector<Point3> l1, std::vector<Point3> l2)
      {
        if (l1.size() != l2.size())
          return false;

        bool ret = true;
        int i = 0;
        while(i < l1.size() && ret)
        {
          Point3 uv1 = l1[i];
          Point3 uv2 = l2[i];
          if((uv1.x != uv2.x) || (uv1.y != uv2.y) || (uv1.z != uv2.z))
            ret = false;

          i++;
        }

        return ret;
      };

      bool operator==(ExVertex const& b)
      {
        return ((vPos.x == b.vPos.x) && (vPos.y == b.vPos.y) && (vPos.z == b.vPos.z) && 
            (vNorm.x == b.vNorm.x) && (vNorm.y == b.vNorm.y) && (vNorm.z == b.vNorm.z) && 
            (vColor.x == b.vColor.x) && (vColor.y == b.vColor.y) && (vColor.z == b.vColor.z) && (vColor.w == b.vColor.w) &&
            (iMaxId == b.iMaxId) && cmpPointList(lTexCoords, b.lTexCoords));
      };

      bool operator!=(ExVertex const& b)
      {
        return ((vPos.x != b.vPos.x) || (vPos.y != b.vPos.y) || (vPos.z != b.vPos.z) || 
            (vNorm.x != b.vNorm.x) || (vNorm.y != b.vNorm.y) || (vNorm.z != b.vNorm.z) || 
            (vColor.x != b.vColor.x) || (vColor.y != b.vColor.y) || (vColor.z != b.vColor.z) || (vColor.w != b.vColor.w) ||
            (iMaxId != b.iMaxId) || (!cmpPointList(lTexCoords, b.lTexCoords)));
      };

      int iMaxId;

      // next same vertex index in vertices list with the same position
      int iNext;
      Point3 vPos;
      Point3 vNorm;
      Point4 vColor;
      std::vector<Point3> lTexCoords;
      std::vector<float> lWeight;
      std::vector<int> lBoneIndex;
  };

	class ExMesh
	{
  public:
  protected:
    std::string m_name;
    ExOgreConverter* m_converter;
    ParamList m_params;
    IGameMesh* m_GameMesh;
    IGameNode* m_GameNode;
    Ogre::Mesh* m_Mesh;
    Box3 m_Bounding;
    ExSkeleton* m_pSkeleton;
    ExBlendShape* m_pBlendShape;
  private:

	public:
		//constructor
		ExMesh(ExOgreConverter* converter, ParamList &params, IGameNode* pGameNode, IGameMesh* pGameMesh, const std::string& name = "");
	  
    //destructor
		~ExMesh();
	
		//write to a OGRE binary mesh
		bool writeOgreBinary();
    
    // get pointer to linked skeleton
    ExSkeleton* getSkeleton();

  protected:
    void buildVertices();
    Ogre::SubMesh* createOgreSubmesh(int matId);
    bool createOgreSharedGeometry();
    void buildOgreGeometry(Ogre::VertexData* vdata, std::vector<ExVertex> verticesList);
		Material* loadMaterial(IGameMaterial* pGameMaterial);
    void getModifiers();
    void loadAnims();
    void loadBlendShapes();
    std::vector<ExAnimation> m_vertexClips;
		std::vector<ExAnimation> m_BSClips;

    //cleaned and sorted vertices
    std::vector<ExVertex> m_vertices;

    //faces with new vertices index
    std::vector<ExFace> m_faces;
  private:
	};

}; // end of namespace

#endif
