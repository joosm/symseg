/*****************************************************************************/
/*  Copyright (c) 2017, Aleksandrs Ecins                                     */
/*  All rights reserved.                                                     */
/*                                                                           */
/*  Redistribution and use in source and binary forms, with or without       */
/*  modification, are permitted provided that the following conditions       */
/*  are met:                                                                 */
/*                                                                           */
/*  1. Redistributions of source code must retain the above copyright        */
/*  notice, this list of conditions and the following disclaimer.            */
/*                                                                           */
/*  2. Redistributions in binary form must reproduce the above copyright     */
/*  notice, this list of conditions and the following disclaimer in the      */
/*  documentation and/or other materials provided with the distribution.     */
/*                                                                           */
/*  3. Neither the name of the copyright holder nor the names of its         */
/*  contributors may be used to endorse or promote products derived from     */
/*  this software without specific prior written permission.                 */
/*                                                                           */
/*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS      */
/*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT        */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT     */
/*  HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   */
/*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT         */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    */
/*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT      */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     */
/*****************************************************************************/

#ifndef VIS_HPP_
#define VIS_HPP_

#include <visualization/pcl_visualization.hpp>
#include <geometry/geometry.hpp>

// State
struct VisState
{
  VisState ()
    : cloudDisplay_ (CLOUD)
    , updateDisplay_ (true)
    , showNormals_ (false)
    , showSymmetry_ (true)
    , showReconstructedCloud_ (false)
    , segIterator_ (0)
    , instanceIdIt_ (0)    
    , pointSize_ (5.0)
    , showFullResolution_ (true)
  {};
  
  enum CloudDisplay   { CLOUD, REFLECTIONAL_SYMMETRIES };
    
  CloudDisplay cloudDisplay_;
  bool updateDisplay_;
  bool showNormals_;
  bool showSymmetry_;
  bool showReconstructedCloud_;
  
  int segIterator_;
  int instanceIdIt_;
  
  float pointSize_;
  bool showFullResolution_;
};

// Callback
void keyboard_callback (const pcl::visualization::KeyboardEvent &event, void *cookie)
{
  VisState* visState = reinterpret_cast<VisState*> (cookie);
  
  if (event.keyUp ())
  {    
    std::string key = event.getKeySym ();
//     cout << key << " key pressed!\n";
    
    visState->updateDisplay_ = true;
    
    // Change segmentation stage displayed
    //if (key == "KP_1")
    if (key == "a")    
    {
      visState->cloudDisplay_ = VisState::CLOUD;
      std::cout << key << std::endl;
    }
    //else if (key == "KP_2")
    else if (key == "s")    
    {
      std::cout << key << std::endl;    
      visState->cloudDisplay_ = VisState::REFLECTIONAL_SYMMETRIES;
    } 
    // Iterators
    else if (key == "Left")
    {
      std::cout << key << std::endl;    
      visState->segIterator_--;
    }      
    else if (key == "Right")
    {
      std::cout << key << std::endl;    
      visState->segIterator_++;
    }
    else if (key == "Down")
    {
      std::cout << key << std::endl;    
      visState->instanceIdIt_--;
    }  
    else if (key == "Up")
    {
      std::cout << key << std::endl;    
      visState->instanceIdIt_++;
    }
    // Point size
    else if (key == "KP_Add")
    {
      std::cout << key << std::endl;    
      visState->pointSize_ += 1.0;
    }
    else if (key == "KP_Subtract")
    {
      std::cout << key << std::endl;    
      visState->pointSize_ = std::max(1.0, visState->pointSize_ - 1.0);    
    }  
        
    // Additional display
    else if ((key == "n") || (key == "N"))
    {
      std::cout << key << std::endl;    
      visState->showNormals_ = !visState->showNormals_;
    }
    else if ((key == "m") || (key == "M"))
    {
      std::cout << key << std::endl;    
      visState->showSymmetry_ = !visState->showSymmetry_;
    }
    else if ((key == "Shift_L") || (key == "comma"))
    {
      std::cout << key << std::endl;    
      visState->showReconstructedCloud_ = !visState->showReconstructedCloud_;    
    }    
    else
      visState->updateDisplay_ = false;
  }
}

#endif // VIS_HPP_