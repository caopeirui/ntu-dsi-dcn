/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2008 INRIA
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 */
#include "ns3/mobility-helper.h"
#include "ns3/mobility-model.h"
#include "ns3/position-allocator.h"
#include "ns3/hierarchical-mobility-model.h"
#include "ns3/log.h"
#include "ns3/pointer.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("MobilityHelper");

MobilityHelper::MobilityHelper ()
{
  m_position = CreateObject<RandomRectanglePositionAllocator> 
    ("X", RandomVariableValue (ConstantVariable (0.0)),
     "Y", RandomVariableValue (ConstantVariable (0.0)));
  m_mobility.SetTypeId ("ns3::StaticMobilityModel");
}
MobilityHelper::~MobilityHelper ()
{}
void 
MobilityHelper::SetPositionAllocator (Ptr<PositionAllocator> allocator)
{
  m_position = allocator;
}
void 
MobilityHelper::SetPositionAllocator (std::string type,
				      std::string n1, const AttributeValue &v1,
				      std::string n2, const AttributeValue &v2,
				      std::string n3, const AttributeValue &v3,
				      std::string n4, const AttributeValue &v4,
				      std::string n5, const AttributeValue &v5,
				      std::string n6, const AttributeValue &v6,
				      std::string n7, const AttributeValue &v7,
				      std::string n8, const AttributeValue &v8,
				      std::string n9, const AttributeValue &v9)
{
  ObjectFactory pos;
  pos.SetTypeId (type);
  pos.Set (n1, v1);
  pos.Set (n2, v2);
  pos.Set (n3, v3);
  pos.Set (n4, v4);
  pos.Set (n5, v5);
  pos.Set (n6, v6);
  pos.Set (n7, v7);
  pos.Set (n8, v8);
  pos.Set (n9, v9);
  m_position = pos.Create ()->GetObject<PositionAllocator> ();
}

void 
MobilityHelper::SetMobilityModel (std::string type,
				  std::string n1, const AttributeValue &v1,
				  std::string n2, const AttributeValue &v2,
				  std::string n3, const AttributeValue &v3,
				  std::string n4, const AttributeValue &v4,
				  std::string n5, const AttributeValue &v5,
				  std::string n6, const AttributeValue &v6,
				  std::string n7, const AttributeValue &v7,
				  std::string n8, const AttributeValue &v8,
				  std::string n9, const AttributeValue &v9)
{
  m_mobility.SetTypeId (type);
  m_mobility.Set (n1, v1);
  m_mobility.Set (n2, v2);
  m_mobility.Set (n3, v3);
  m_mobility.Set (n4, v4);
  m_mobility.Set (n5, v5);
  m_mobility.Set (n6, v6);
  m_mobility.Set (n7, v7);
  m_mobility.Set (n8, v8);
  m_mobility.Set (n9, v9);
}

void 
MobilityHelper::PushReferenceMobilityModel (Ptr<Object> reference)
{
  Ptr<MobilityModel> mobility = reference->GetObject<MobilityModel> ();
  m_mobilityStack.push_back (mobility);
}
void 
MobilityHelper::PopReferenceMobilityModel (void)
{
  m_mobilityStack.pop_back ();
}


std::string 
MobilityHelper::GetMobilityModelType (void) const
{
  return m_mobility.GetTypeId ().GetName ();
}

void 
MobilityHelper::Install (NodeContainer c)
{
  for (NodeContainer::Iterator i = c.Begin (); i != c.End (); ++i)
    {
      Ptr<Object> object = *i;
      Ptr<MobilityModel> model = object->GetObject<MobilityModel> ();
      if (model == 0)
	{
	  model = m_mobility.Create ()->GetObject<MobilityModel> ();
	  if (model == 0)
	    {
	      NS_FATAL_ERROR ("The requested mobility model is not a mobility model: \""<< 
			      m_mobility.GetTypeId ().GetName ()<<"\"");
	    }
	  if (m_mobilityStack.empty ())
	    {
	      NS_LOG_DEBUG ("node="<<object<<", mob="<<model);
	      object->AggregateObject (model);
	    }
	  else
	    {
	      // we need to setup a hierarchical mobility model
	      Ptr<MobilityModel> parent = m_mobilityStack.back ();
	      Ptr<MobilityModel> hierarchical = 
		CreateObject<HierarchicalMobilityModel> ("Child", PointerValue (model),
							 "Parent", PointerValue (parent));
	      object->AggregateObject (hierarchical);
	      NS_LOG_DEBUG ("node="<<object<<", mob="<<hierarchical);
	    }
	}
      Vector position = m_position->GetNext ();
      model->SetPosition (position);
    }
}

void 
MobilityHelper::InstallAll (void)
{
  Install (NodeContainer::GetGlobal ());
}

} // namespace ns3