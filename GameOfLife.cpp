/**
 * @brief Samu has learnt the rules of Conway's Game of Life
 *
 * @file GameOfLife.h
 * @author  Norbert Bátfai <nbatfai@gmail.com>
 * @version 0.0.1
 *
 * @section LICENSE
 *
 * Copyright (C) 2015, 2016 Norbert Bátfai, batfai.norbert@inf.unideb.hu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 *
 * Samu (Nahshon) has learnt the rules of Conway's Game of Life. This is
 * an example of the paper entitled "Samu in his prenatal development".
 */

#include "GameOfLife.h"

GameOfLife::GameOfLife ( int w, int h ) : m_w ( w ), m_h ( h )
{
  lattices = new int**[2];
  lattices[0] = new int*[m_h];
  for ( int i {0}; i<m_h; ++i )
    {
      lattices[0][i] = new int [m_w];
    }
  lattices[1] = new int*[m_h];
  for ( int i {0}; i<m_h; ++i )
    {
      lattices[1][i] = new int [m_w];
    }

  predictions = new int*[m_h];
  for ( int i {0}; i<m_h; ++i )
    {
      predictions[i] = new int [m_w];
    }

  samuQl = new QL*[m_h];
  for ( int i {0}; i<m_h; ++i )
    {
      samuQl[i] = new QL [m_w];
    }

  latticeIndex = 0;
  int ** lattice = lattices[latticeIndex];
  for ( int i {0}; i<m_h; ++i )
    for ( int j {0}; j<m_w; ++j )
      {
        lattice[i][j] = 0;
      }

  /*
  glider ( lattice, 2*m_w/5, 2*m_h/5 );
  glider ( lattice, 3*m_w/5, 3*m_h/5 );
  glider ( lattice, 4*m_w/5, 4*m_h/5 );
  glider ( lattice, 4*m_w/5, 2*m_h/5 );
  glider ( lattice, 2*m_w/5, 4*m_h/5 );
  */

  /*
  carx = 0;
  manx = m_w/2;
  housex = 2*m_w/5;

  house ( lattice, housex, 3*m_h/5 -6 );
  car ( lattice, carx, 3*m_h/5 +1 );
  man ( lattice, manx, 3*m_h/5-1 );
  */

  red ( lattice, 2, 5, 1 );


}

int ** GameOfLife::lattice()
{
  return lattices[latticeIndex];
}

void GameOfLife::run()
{
  while ( true )
    {
      QThread::msleep ( m_delay );

      if ( !paused )
        {
          ++m_time;
          development();
          learning();
          latticeIndex = ( latticeIndex+1 ) %2;
          emit cellsChanged ( lattices[latticeIndex], predictions );
        }
    }

}

void GameOfLife::pause()
{
  paused = !paused;
}

int GameOfLife::numberOfNeighbors ( int **lattice, int r, int c, int state )
{
  int number {0};

  for ( int i {-1}; i<2; ++i )
    for ( int j {-1}; j<2; ++j )

      if ( ! ( ( i==0 ) && ( j==0 ) ) )
        {
          int o = c + j;
          if ( o < 0 )
            {
              o = m_w-1;
            }
          else if ( o >= m_w )
            {
              o = 0;
            }

          int s = r + i;
          if ( s < 0 )
            {
              s = m_h-1;
            }
          else if ( s >= m_h )
            {
              s = 0;
            }

          if ( lattice[s][o] == state )
            {
              ++number;
            }
        }

  return number;
}

void GameOfLife::development()
{

  int **prevLattice = lattices[latticeIndex];
  int **nextLattice = lattices[ ( latticeIndex+1 ) %2];

  /*
  for ( int i {0}; i<m_h; ++i )
    {
      for ( int j {0}; j<m_w; ++j )
        {

          int liveNeighbors = numberOfNeighbors ( prevLattice, i, j, true );

          if ( prevLattice[i][j] == true )
            {
              if ( liveNeighbors==2 || liveNeighbors==3 )
                {
                  nextLattice[i][j] = true;
                }
              else
                {
                  nextLattice[i][j] = false;
                }
            }
          else
            {
              if ( liveNeighbors==3 )
                {
                  nextLattice[i][j] = true;
                }
              else
                {
                  nextLattice[i][j] = false;
                }
            }
        }
    }
    */

  for ( int i {0}; i<m_h; ++i )
    {
      for ( int j {0}; j<m_w; ++j )
        {

          nextLattice[i][j] = 0;

        }
    }


  ++age;
  if ( age <20 )
    {
      red ( nextLattice, 2, 5, 1 );
    }
  else if ( age <40 )
    {
      red ( nextLattice, 2, 5, 2 );
    }
  else if ( age <60 )
    {
      red ( nextLattice, 2, 5, 3 );
    }
  else if ( age <80 )
    {
      green ( nextLattice, 2, 5, 1 );
    }
  else if ( age <100 )
    {
      green ( nextLattice, 2, 5, 2 );
    }
  else if ( age <120 )
    {
      green ( nextLattice, 2, 5, 3 );
    }
  else if ( age <140 )
    {
      blue ( nextLattice, 2, 5, 1 );
    }
  else if ( age <160 )
    {
      blue ( nextLattice, 2, 5, 2 );
    }
  else if ( age <180 )
    {
      blue ( nextLattice, 2, 5, 3 );
    }
  else
    {
      age =0;
      //red ( nextLattice, 2, 5, 2 );
    }


  /*
  if ( carx < m_w-5 )
  carx += 2;
  else
  carx = 0;

  if ( manx < m_w-3 )
  ++manx;
  else
  manx = 0;

  house ( nextLattice, housex, 3*m_h/5 -6 );
  car ( nextLattice, carx, 3*m_h/5 +1 );
  man ( nextLattice, manx, 3*m_h/5-1 );
  */

}


GameOfLife::~GameOfLife()
{
  for ( int i {0}; i<m_h; ++i )
    {
      delete[] lattices[0][i];
      delete[] lattices[1][i];
      delete[] predictions[i];
      delete[] samuQl[i];
    }

  delete[] samuQl;
  delete[] predictions;
  delete[] lattices[0];
  delete[] lattices[1];
  delete[] lattices;

}


void GameOfLife::red ( int **lattice, int x, int y, int color )
{

  int r[7][17] =
  {
    {1,1,1,0,0,0,1,1,1,1,1,0,1,1,1,0,0},
    {1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0},
    {1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,1},
    {1,1,1,0,0,0,1,1,1,1,0,0,1,0,0,0,1},
    {1,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
    {1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0},
    {1,0,0,0,1,0,1,1,1,1,1,0,1,1,1,0,0}
  };

  for ( int i {0}; i<7; ++i )
    {
      for ( int j {0}; j<17; ++j )
        {
          lattice[y+i][x+j] = r[i][j]*color;

        }

    }
}


void GameOfLife::green ( int **lattice, int x, int y, int color )
{

  int r[7][29] =
  {
    {0,1,1,1,0,0,1,1,1,0,0,0,1,1,1,1,1,0,1,1,1,1,1,0,1,0,0,0,1},
    {1,0,0,0,1,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,1,0,0,1},
    {1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,1,1,0,1},
    {1,0,1,1,1,0,1,1,0,0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,0,1,0,1},
    {1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,1,1,1},
    {1,0,0,0,1,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,1},
    {0,1,1,1,0,0,1,0,0,0,1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,0,0,0,1}
  };

  for ( int i {0}; i<7; ++i )
    {
      for ( int j {0}; j<29; ++j )
        {
          lattice[y+i][x+j] = r[i][j]*color;

        }

    }
}

void GameOfLife::blue ( int **lattice, int x, int y, int color )
{

  int r[7][21] =
  {
    {1,1,1,0,0,1,0,0,0,0,1,0,0,0,1,0,1,1,1,1,1},
    {1,0,0,1,0,1,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0},
    {1,0,0,1,0,1,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0},
    {1,1,1,0,0,1,0,0,0,0,1,0,0,0,1,0,1,1,1,1,0},
    {1,0,0,1,0,1,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0},
    {1,0,0,1,0,1,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0},
    {1,1,1,0,0,1,1,1,1,0,0,1,1,1,0,0,1,1,1,1,1}

  };

  for ( int i {0}; i<7; ++i )
    {
      for ( int j {0}; j<21; ++j )
        {
          lattice[y+i][x+j] = r[i][j]*color;

        }

    }
}



/*
void GameOfLife::glider ( bool **lattice, int x, int y )
{

  lattice[y+0][x+2] = true;
  lattice[y+1][x+1] = true;
  lattice[y+2][x+1] = true;
  lattice[y+2][x+2] = true;
  lattice[y+2][x+3] = true;

}


void GameOfLife::house ( bool **lattice, int x, int y )
{

  lattice[y+0][x+3] = true;

  lattice[y+1][x+2] = true;
  lattice[y+1][x+4] = true;

  lattice[y+2][x+1] = true;
  lattice[y+2][x+5] = true;

  lattice[y+3][x+0] = true;
  lattice[y+3][x+6] = true;

  lattice[y+4][x+0] = true;
  lattice[y+4][x+6] = true;

  lattice[y+5][x+0] = true;
  lattice[y+5][x+6] = true;

  lattice[y+6][x+0] = true;
  lattice[y+6][x+6] = true;

  lattice[y+7][x+0] = true;
  lattice[y+7][x+6] = true;

  lattice[y+8][x+0] = true;
  lattice[y+8][x+1] = true;
  lattice[y+8][x+2] = true;
  lattice[y+8][x+3] = true;
  lattice[y+8][x+4] = true;
  lattice[y+8][x+5] = true;
  lattice[y+8][x+6] = true;
}


void GameOfLife::man ( bool **lattice, int x, int y )
{

  lattice[y+0][x+1] = true;

  lattice[y+1][x+0] = true;
  lattice[y+1][x+1] = true;
  lattice[y+1][x+2] = true;

  lattice[y+2][x+1] = true;

  lattice[y+3][x+0] = true;
  lattice[y+3][x+2] = true;

}


void GameOfLife::car ( bool **lattice, int x, int y )
{

  lattice[y+0][x+1] = true;
  lattice[y+0][x+2] = true;
  lattice[y+0][x+3] = true;

  lattice[y+1][x+0] = true;
  lattice[y+1][x+1] = true;
  lattice[y+1][x+2] = true;
  lattice[y+1][x+3] = true;
  lattice[y+1][x+4] = true;

  lattice[y+2][x+1] = true;
  lattice[y+2][x+3] = true;

}
*/

int GameOfLife::getW() const
{
  return m_w;
}
int GameOfLife::getH() const
{
  return m_h;
}
long GameOfLife::getT() const
{
  return m_time;
}

void GameOfLife::learning()
{
  int **lattice = lattices[latticeIndex];
//bool **lattice = lattices[( latticeIndex+1 ) %2];

  double img_input[40];
  int colors[4] = {0,0,0,0};

  for ( int r {0}; r<m_h; ++r )
    {
      for ( int c {0}; c<m_w; ++c )
        {

          std::stringstream ss;
          int ii {0};

          colors[0] = colors[1] = colors[2] = colors[3] = 0;


          for ( int i {-1}; i<2; ++i )
            for ( int j {-1}; j<2; ++j )

              if ( ! ( ( i==0 ) && ( j==0 ) ) )

                {
                  int o = c + j;
                  if ( o < 0 )
                    {
                      o = m_w-1;
                    }
                  else if ( o >= m_w )
                    {
                      o = 0;
                    }

                  int s = r + i;
                  if ( s < 0 )
                    {
                      s = m_h-1;
                    }
                  else if ( s >= m_h )
                    {
                      s = 0;
                    }

                  //ss << lattice[s][o];

                  //if ( lattice[s][o] ) ++ii;
                  ++colors[lattice[s][o]];

                  //img_input[ii++] = lattice[s][o]?1.2:-1.2;

                } // if

          //std::string iis[] = {"egy", "ketto", "harom", "negy", "ot", "hat", "het", "nyolc"};

          /*
           std::string iis[] = {
          "11111111",
          "22222222",
          "33333333",
          "44444444",
          "55555555",
          "66666666",
          "77777777",
          "88888888"};
          */
          char stmt_buffer[40];
          std::memset ( stmt_buffer, 0, 40 );
          //std::snprintf ( stmt_buffer, 40, "cell is %s %s are live",  lattice[r][c]?"true":"false", iis[ii].c_str());
          //std::snprintf ( stmt_buffer, 16, "%s%s",  lattice[r][c]?"tttttttt":"ffffffff", iis[ii].c_str());
          //QString q (stmt_buffer);
          //qDebug() <<q;

          /*
          for(int t=0; t<40;++t)
          img_input[t] = ((double)stmt_buffer[t]);
          */
          /*
                    img_input[0] = lattice[r][c] / 10.0; //lattice[r][c]?1.0:-1.0;
                    img_input[1] = ( ( double ) colors[0] ) / ( double ) 10.0;
                    img_input[2] = ( ( double ) colors[1] ) / ( double ) 10.0;
                    img_input[3] = ( ( double ) colors[2] ) / ( double ) 10.0;
                    img_input[4] = ( ( double ) colors[3] ) / ( double ) 10.0;
          */

          img_input[0] = lattice[r][c]; //lattice[r][c]?1.0:-1.0;
          img_input[1] =  colors[0]  ;
          img_input[2] =   colors[1]  ;
          img_input[3] = colors[2]  ;
          img_input[4] =   colors[3]  ;

          ss << img_input[0];
          ss << '|';

          ss << colors[0]; //img_input[1];
          ss << '|';
          ss << img_input[2];
          ss << '|';
          ss << img_input[3];
          ss << '|';
          ss << img_input[4];

          std::string prg = ss.str();

          //SPOTriplet response = samuQl[r][c] ( lattice[r][c], prg, img_input );
          SPOTriplet response = samuQl[r][c] ( lattice[r][c], prg );
          predictions[r][c] = response;

        }

    }

}












