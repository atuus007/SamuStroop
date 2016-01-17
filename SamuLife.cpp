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

#include "SamuLife.h"

SamuLife::SamuLife ( int w, int h, QWidget *parent ) : QMainWindow ( parent )
{
  setWindowTitle ( "SamuStroop" );
  setFixedSize ( QSize ( 2*w*m_cw, h*m_ch ) );

  gameOfLife = new GameOfLife ( w, h );
  gameOfLife->start();

  connect ( gameOfLife, SIGNAL ( cellsChanged ( int **, int ** ) ),
            this, SLOT ( updateCells ( int **, int ** ) ) );

}

void SamuLife::updateCells ( int **lattice, int **prediction )
{
  this->lattice = lattice;
  this->prediction = prediction;
  update();
}

void SamuLife::paintEvent ( QPaintEvent* )
{
  QPainter qpainter ( this );



  for ( int i {0}; i<gameOfLife->getH(); ++i )
    {
      for ( int j {0}; j<gameOfLife->getW(); ++j )
        {

          if ( lattice )
            {
              if ( lattice[i][j] == 1 )
                qpainter.fillRect ( j*m_cw, i*m_ch,
                                    m_cw, m_ch, Qt::red );
              else if ( lattice[i][j] == 2 )
                qpainter.fillRect ( j*m_cw, i*m_ch,
                                    m_cw, m_ch, Qt::green );
              else if ( lattice[i][j] == 3 )
                qpainter.fillRect ( j*m_cw, i*m_ch,
                                    m_cw, m_ch, Qt::blue );
              else
                qpainter.fillRect ( j*m_cw, i*m_ch,
                                    m_cw, m_ch, Qt::white );
            }
          if ( prediction )
            {
              if ( prediction[i][j] == 1 )
                qpainter.fillRect ( gameOfLife->getW() *m_cw + j*m_cw, i*m_ch,
                                    m_cw, m_ch, Qt::red );
              else if ( prediction[i][j] == 2 )
                qpainter.fillRect ( gameOfLife->getW() *m_cw + j*m_cw, i*m_ch,
                                    m_cw, m_ch, Qt::green );
              else if ( prediction[i][j] == 3 )
                qpainter.fillRect ( gameOfLife->getW() *m_cw + j*m_cw, i*m_ch,
                                    m_cw, m_ch, Qt::blue );
              else
                qpainter.fillRect ( gameOfLife->getW() *m_cw + j*m_cw, i*m_ch,
                                    m_cw, m_ch, Qt::white );
            }
          qpainter.setPen ( QPen ( Qt::lightGray, 1 ) );

          qpainter.drawRect ( j*m_cw, i*m_ch,
                              m_cw, m_ch );

          qpainter.setPen ( QPen ( Qt::darkGray, 1 ) );

          qpainter.drawRect ( gameOfLife->getW() *m_cw + j*m_cw, i*m_ch,
                              m_cw, m_ch );

        }
    }

  qpainter.setPen ( QPen ( Qt::black, 1 ) );

  qpainter.drawLine ( gameOfLife->getW() *m_cw, 0,
                      gameOfLife->getW() *m_cw,gameOfLife->getH() *m_ch );

  QFont font = qpainter.font() ;
  font.setPointSize ( 28 );
  qpainter.setFont ( font );
  qpainter.setPen ( QPen ( Qt::black, 1 ) );
  qpainter.drawText ( 40, 60, "Reality" );
  qpainter.setPen ( QPen ( Qt::black, 1 ) );
  qpainter.drawText ( gameOfLife->getW() *m_cw +40, 60, "Samu's prediction" );
  qpainter.setPen ( QPen ( Qt::darkGray, 1 ) );
  qpainter.drawText ( 40, gameOfLife->getH() *m_ch - 30 , QString::number ( gameOfLife->getT() ) );

  qpainter.end();
}

void SamuLife::keyPressEvent ( QKeyEvent * event )
{
  if ( event->key() == Qt::Key_Space )
    {
      gameOfLife->pause();
    }
  else if ( event->key() == Qt::Key_D ) //Qt::Key_division )
    {
      gameOfLife->setDelay ( gameOfLife->getDelay() / 2.0 );
    }
  else if ( event->key() == Qt::Key_M ) //Qt::Key_multiply )
    {
      gameOfLife->setDelay ( gameOfLife->getDelay() * 2.0 );
    }
}

SamuLife::~SamuLife()
{
  delete gameOfLife;
}

