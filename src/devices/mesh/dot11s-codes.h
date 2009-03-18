/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2008,2009 IITP RAS
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
 * Authors: Aleksey Kovalenko <kovalenko@iitp.ru>
 *          Kirill Andreev <andreev@iitp.ru>
 */


#ifndef DOT11S_CODES_H
#define DOT11S_CODES_H

#include "wifi-information-element.h"

namespace ns3 {

/**
 * \ingroup mesh
 */
enum dot11sReasonCode {
  REASON11S_PEER_LINK_CANCELLED,
  REASON11S_MESH_MAX_PEERS,
  REASON11S_MESH_CAPABILITY_POLICY_VIOLATION,
  REASON11S_MESH_CLOSE_RCVD,
  REASON11S_MESH_MAX_RETRIES,
  REASON11S_MESH_CONFIRM_TIMEOUT,
  REASON11S_MESH_SECURITY_ROLE_NEGOTIATION_DIFFERS,
  REASON11S_MESH_SECURITY_AUTHENTICATION_IMPOSSIBLE,
  REASON11S_MESH_SECURITY_FAILED_VERIFICATION,
  REASON11S_MESH_INVALID_GTK,
  REASON11S_MESH_MISMATCH_GTK,
  REASON11S_MESH_INCONSISTENT_PARAMETERS,
  REASON11S_MESH_CONFIGURATION_POLICY_VIOLATION,
  REASON11S_RESERVED,
};

/**
 * \ingroup mesh
 */
enum dot11sStatusCode {
  STATUS11S_PEAR_LINK_ESTABLISHED,
  STATUS11S_PEAR_LINK_CLOSED,
  STATUS11S_NO_LISTED_KEY_HOLDER,
  STATUS11S_MESH_KEY_HANDSHAKE_MALFORMED,
  STATUS11S_PEAR_LINK_MAX_RETRIES,
  STATUS11S_PEAR_LINK_NO_PMK,
  STATUS11S_PEAR_LINK_ALT_PMK,
  STATUS11S_PEAR_LINK_NO_AKM,
  STATUS11S_PEAR_LINK_ALT_AKM,
  STATUS11S_PEAR_LINK_NO_KDF,
  STATUS11S_PEAR_LINK_SA_ESTABLISHED,
  STATUS11S_AUTHENTICATION_REJECTED_CLOGGING,
  STATUS11S_RESERVED,
};

}
#endif
