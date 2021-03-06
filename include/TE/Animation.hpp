/*
 * File: Animation.hpp
 * Project: Project-TE
 * Created Date: Sunday December 8th 2019
 * Author: bitDaft
 * -----
 * Last Modified: Tuesday, March 24th 2020 4:33:29 pm
 * Modified By: bitDaft at (ajaxhis@tutanota.com>)
 * -----
 * Copyright (c) 2019 bitDaft
 */

#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <vector>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>


// ! this is going to be considered as a resource,
// ! so there is no need to remove any rects. let all the rects be created at start
// ! since the textures are only going to be loaded once and the animation on that is fixed and since it is available globally
// ! let the animations for that texture also be created at the same time and be accessible globally as a resource

/** 
 * Holds the frames needed for an animation used by an AnimatedSprite
*/
class Animation
{
public:
  // constructor destructor
  Animation(const int &&reserve = 10);
  virtual ~Animation();

  /**
   * Add a new frame to the current animation  
   * @param rect the rect that denotes the frames of the animation from a texture
   * @param count the number of times to enter the frames
   * @return void
   */
  void addFrame(const sf::IntRect *rect, int count = 1);

  /**
   * Sets the texture needed for this animation frames  
   * @param texture a reference to the texture
   * @return void
   */
  void setTexture(const sf::Texture &texture);

  /**
   * Gets the number of frames in the stored animation  
   * @return int the count of frames
   */
  int getFrameCount() const;

  /**
   * Gets the nth frame   
   * @param pos the position of the frame in the animation
   * @return const sf::IntRect & reference to the frame
   */
  const sf::IntRect &getFrame(int pos) const;

  /**
   * Get a reference to the texture   
   * @return const sf::Texture & a reference to the stored texture
   */
  const sf::Texture &getTexture() const;

  /**
   * Prevent the freeing of memory used by the frames when the animation is destroyed
   * may come in use if the frames need to be resused
   * @return void
   */
  void preventRelease();

private:
  const sf::Texture *refTex;
  std::vector<const sf::IntRect *> frames;
  bool _c;
};

#endif