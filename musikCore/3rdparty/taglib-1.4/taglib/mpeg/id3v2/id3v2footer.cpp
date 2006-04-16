/***************************************************************************
    copyright            : (C) 2002, 2003 by Scott Wheeler
    email                : wheeler@kde.org
 ***************************************************************************/

/***************************************************************************
 *   This library is free software; you can redistribute it and/or modify  *
 *   it  under the terms of the GNU Lesser General Public License version  *
 *   2.1 as published by the Free Software Foundation.                     *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful, but   *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  *
 *   USA                                                                   *
 ***************************************************************************/

#include "id3v2footer.h"
#include "id3v2header.h"

using namespace TagLib;
using namespace ID3v2;

class Footer::FooterPrivate
{
public:
  static const uint size = 10;
};

Footer::Footer()
{

}

Footer::~Footer()
{

}

const unsigned int Footer::size()
{
  return FooterPrivate::size;
}

ByteVector Footer::render(const Header *header) const
{
    ByteVector headerData = header->render();
    headerData[0] = '3';
    headerData[1] = 'D';
    headerData[2] = 'I';
    return headerData;
}
