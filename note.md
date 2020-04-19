# NOTES

now that we have set up a simple game object and linked to the libs properly, it is time we discussed how exactly we are going to make this.

lets define our grid first.

the grid is going to be 10 x 10. each cell is going to be 10px x 10px. this will give a grid of 100px x 100px.  
since we have the real estate lets double it. 20 x 20 grid with 20px x 20px. should gi9ve us 400px x 400px. this will just fit in our screen height.

next, should the grid be drawn. normally in games the grid can be toggled on or off. so the grid map is layer of its own which may or may not be drawn.

the grid drawn is not drawn cell by cell. let say the cell has a border of 1px. if we draw cell by cell adjacent cell will cause the border to be 2px thick.  
so we need to do border collapse. but that cant be done via sprite or textures. so we are going to need to generate the texture for it dynamically, since the dimensions of the grid may change from level to level, and making static texture is going to be tedious to stitch together.

so we are going to have the grid obj be drawable.it is not animated so a sprite should do. for the texture we are going to generate it once at the beginning. so maybe in the constructor. or in the init function. but this way of generating this texture cannot be used with the resource system. so we need to have a method in resource to load a generated texture as part of the resource sytem.

~~TASK 1 : give method in resourceManager to load a generated texture obj.~~DONE

where should we initialize this texture. inside the obj makes no sense if multiple of the entities are created. so multiple generation. should we generate in the game obj itself. but then it will become bloatedwith unnecessary loaders i feel. what about loaders in between screens like it is usually done. how does that loading work  
maybe we will make a loader obj, whose sole purpose or functor is to load the resources into the resoureManager with the predefined handles.

but currently for this specific situation we will just initialize this texture in the constructor or init of the game obj.  
but we need to add the functionality to add generated texture to the resource manager.  
so i will be back once the adding of dynamic functionality has been added to the engine.  

i have added functionality to add texture from ptr.
now lets generate the texture for the grid that we need and display it.

----------------------------------------------

Now we have the grid being displayed and the texture us being generated.
no we need a sprite to show the tile that is currently selected.
so lets open up asesprite and make it.

ok now we have made a simple grid location selector cursor.  
now we need to make this cursor object along with animatedsprite and movement controls for the cursor.  
so lets make that cursor object now.  


now that we have a cursor and we can move itr around, we need to have it stick to the grid locations.  
meaning it cannot have continuos values, but discrete values from the grid.  
if the cursor where to hold its own position it would also need to know on what position of the grid it is and what the start location of the grid and other details of the grid.  
but if the grid kept track of the cursor then the grid can just tell the cursor to go to whatever location the grid tells.   
and the cursor need not bother with keeping track of any details or having any functions to send data to grid when its position changes.  
so now we have lifted state of the cursor up into the grid class.  
so now thegrid will handle input or cursor and it will calculate the new location and send the new position to cursor. the cursor only need to react to its position change. just like react hehe.  

so the cursor states have been lifted into the grid class.now lets change the handle accordingly to wrok properly.

grid movement indiscrete steps as well as blocky movement done.


so with that the initial goal of the project has been reached.
we have created a grid with a cursor that can navigate the grid in discrete steps.
