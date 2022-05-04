# Cutscene Manager Research

I am Robert Recordà Illas, student of the Bachelor's Degree in Video Game Design and Development at UPC. The following content is generated for the second year's subject Project 2.

## Introduction

A cutscene (also often refered as Event scene) is a sequence that helps develop the story by showing conversation between characters, can be used to reward players, often shows characters in action and can also be used to create mood or emotions.

## Cases of use

### Introduction or Open Cinematic
This is the inital cutscene in a video game. It is usually a video and it helps introduce the world, the character and the events that lead to the current situation of the world.

**Back-story:**
[Elden Ring](https://www.youtube.com/watch?v=_uydEN9Fu7M)\
**Plot:**
[Warcraft III](https://www.youtube.com/watch?v=jUmvrk0yVxU)\
**Action:**
[Final Fantasy VII Remake](https://www.youtube.com/watch?v=qCmFgb1eE54)\
**Mood/Emotion:**
[World of Warcraft](https://www.youtube.com/watch?v=vlVSJ0AvZe0)

### In-Between
This cutscene cuts the gameplay, it is often used as a reward or as a way to advance the plot.

**Plot:**
[Final Fantasy XIV](https://www.youtube.com/watch?v=3MFYXNc76nc)\
**Reward:**
[Final Fantasy XIV Shadowbringers](https://youtu.be/3MFYXNc76nc?t=1254)

### Final
The last cutscene in a video game. This is generally the best cutscene and the one where the player must experience the highest ecstasy of emotions. It serves also as the final reward in a game. This cutscene can close the story and even introduce clip hanggers to make players feel like they want more.

[Zelda Breath of the Wild](https://www.youtube.com/watch?v=y9sZPqiLq50)

## Types of Cutscenes
#### Live-action
This are cutscene with real actors instead of rendered characters. This types of cutscenes have become less used nowadays due to the ability of render or pre-render realistic cutscenes.

[Inscryption](https://youtu.be/wWDRv69oDZ0?t=92)

### Pre-rendered
This are animated cutscenes that are already rendered and stored in the game.

[Elden Ring](https://youtu.be/c9akEr9y7XA?t=12)

### Mixed media
This cutscenes are made by combining Live-action with Pre-rendered cutscenes. Those are made by real actors on a rendered background.

[Wing Commander 3](https://youtu.be/4giX0Y01p0Q?t=6170)

### Interactive
This type of cutscenes is the most unique one, this one implies the player taking control of the action by pressing buttons or a sequence of buttons while this appear on the screen.

[Spiderman 3](https://youtu.be/5Js72d-LpEI)

### In game engine or Real time
This is types of cutscenes are rendered by the player's systems graphic card.
This cutscenes tend to have lower quality compared to the other types of cutscenes since they use the same render that the engine is using for the gameplay.

[Halo Infinite](https://www.youtube.com/watch?v=WqwbtvuXw60)


## Other Engines solution

In commercial engines there is a tool where you have a time bar and you can add elements, characteristics and attributes through time. You can set frames where attributes and properties of the objects are modified or set this points as interpolations of movement, scale, colour, effects and many more things

Here there are some video examples of how cutscenes are made:

[Unity](https://www.youtube.com/watch?v=Tg-ydfLEPak)\
[Unreal Engine](https://www.youtube.com/watch?v=7dVHhwGBCQQ)

## How to make a Real time Cutscene Manager


### Setup
This "instruction" is special and can only be used at the beggining of the script, its used to create entities, images, text or any other thing that is not currently being rendered. The things created inside setup will only appear in this cutscene and will be deleted once the cutscene finish.

There are 3 types of setup

#### Label

tag --> Identifies the Label, is like an ID. (int)\
posX --> Position in the X axis of the screen. (int)\
posY --> Position in the Y axis of the screen. (int)\
scale --> Scale of the text. (float)

```XML
<cutscene title="test">
    <Setup>
        <Label tag="Name_lbl" posX="160" posY="198" scale="0.2" />
    </Setup>
</cutscene>
```

#### Image

tag --> Identifies the Image, is like an ID (Must be unique on the entire running Game). (String)\
path --> The direction where the image that you want to load is stored. (String)
posX --> Position in the X axis of the screen. (int)\
posY --> Position in the Y axis of the screen. (int)\
scale --> Scale of the text. (float)

```XML
<cutscene title="test">
    <Setup>
        <Image tag="Chat" path="Assets/Sprites/UI/Chat_box.png" posX="128" posY="192" scale="0.5" />
    </Setup>
</cutscene>
```

#### Entities

This one has sub-divisions to ease the loading process.\

**Entities:** Is used as a way to wrap all the Entities that are going to be created, this way my engine loads or the entities at the same iteration of the game.

**Entity:** Wraps all the data of one entity, by having sub-commands inside of Entity, the engine allows to load uncompleted Entities if desired, for example, we could load an Entity without texture or without animations.\
tag--> Identifies the Entity, is like an ID (Must be unique on the entire running Game). (String)\

**Position:** Gives a position to the entity:
posX --> Position in the X axis on the scene. (int)\
posY --> Position in the Y axis on the scene. (int)

**Texture:** loads a texture for the entity.\
layer --> At which layer is going to be rendered. (int)\
orderInLayer --> At which position inside the layer is going to be rendered. (float)\
scale --> The scale of the texture. (float)\
path --> The direction where the texture that you want to load is stored. (String)

**Animations:** Is used to wrap all the animations that the entity will have, due to Engines and code limitation, there are only
11 Animations that can be loaded by Entity (It can be changed in the engine's code if the game requires more or less)
Each of this 11 animations have a name and can only be one by entity.

*Idle, Walk_up, Walk_down, Walk_left, Walk_right, Attack, A_one, A_two, A_three, A_four, A_five*

**Animation:** Is used to load an individual animation.\
name --> The name of the animation
loop --> Is the animation a loop? (Boolean)\
frames --> The number of frames that the animation has. (int)\
width --> The width of the animation in the loaded texture. (int)\
height --> The height of the animation in the loaded texture. (int)\
line --> The line of the animation in the loaded texture. (int)\
speed --> The speed which the animation changes frames. (float)\
```XML
<cutscene>
    <Setup>
        <Entities>
        	<Entity tag="Emily">
        		<Position posX="-60" posY="736" />
        		<Texture layer="1" orderInLayer="3.0" scale="1.0" path="Assets/Sprites/Emily.png" />
        		    <Animations>
        				<Animation name="Walk_up" loop="true" frames="6" width="32" height="64" line="1" speed="0.10f" />
        				<Animation name="Walk_down" loop="true" frames="6" width="32" height="64" line="2" speed="0.10f" />
        				<Animation name="Walk_left" loop="true" frames="6" width="32" height="64" line="3" speed="0.10f" />
        				<Animation name="Walk_right" loop="true" frames="6" width="32" height="64" line="4" speed="0.10f" />
        		</Animations>
        	</Entity>
        	<Entity tag="Will">
        		<Position posX="1024" posY="736" />
        		<Texture layer="1" orderInLayer="3.0" scale="1.0" path="Assets/Sprites/Will.png" />
        		<Animations>
        			<Animation name="Walk_up" loop="true" frames="6" width="32" height="64" line="1" speed="0.10f" />
        			<Animation name="Walk_down" loop="true" frames="6" width="32" height="64" line="2" speed="0.10f" />
        			<Animation name="Walk_left" loop="true" frames="6" width="32" height="64" line="3" speed="0.10f" />
        		    <Animation name="Walk_right" loop="true" frames="6" width="32" height="64" line="4" speed="0.10f" />
        		</Animations>
            </Entity>
        </Entities>
    </Setup>
</cutscene>
```

### Instructions

Instructions come after the setup, they are used as commands for the action. All instructions have a similar syntaxis in order to ease the writing of scripts.\
First it has to who the instruction is pointing **"Camera"** and then what it does **"Target"** --> **"CameraTarget"** moves the camera to the target and makes it move with it.

Almost all instructions require a time that will serve as the duration of the action and the time until the next instruction.

#### Wait

This one is the simplest instruction. It's used to stop the action for a certain time.

time --> Marks the duration of this instruction. (float)

```XML
<cutscene>
    <Wait time="0.8f" />
</cutscene>
```

#### Camera

This instruction moves the camera.

posX --> Position in the X axis on the scene. (int)\
posY --> Position in the Y axis on the scene. (int)\
time --> Marks the duration of this instruction. (float)

```XML
<cutscene>
    <Camera posX="224" posY="736" time="0.0f"/>
</cutscene>
```

#### CameraTarget

This instruction moves the camera to the target and makes it move with it.

tag --> The tag of the Entity that will target. (String)\
time --> Marks the duration of this instruction. (float)

```XML
<cutscene>
    <CameraTarget tag="Emily" time="0.01f" />
</cutscene>
```

#### CameraDisplacement

This instruction displaces the camera.

speedX --> Speed in the X axis. (int)\
speedY --> Speed in the Y axis. (int)\
time --> Marks the duration of this instruction. (float)

```XML
<cutscene>
    <CameraDisplacement speedX="200.0" speedY="0.0" time="5.5" />
</cutscene>
```

#### EntityMove

Displaces the entity along the scene

tag --> The tag of the Entity that will target. (String)\
speedX --> Speed in the X axis. (int)\
speedY --> Speed in the Y axis. (int)\
time --> Marks the duration of this instruction. (float)

```XML
<cutscene>
    <EntityMove tag="Will" speedX="-60" speedY="0" time="3.8" />
</cutscene>
```

#### EntityAnimation

Changes the animation of an Entity

tag --> The tag of the Entity that will target. (String)\
name --> The name of the animation. (float)

```XML
<cutscene>
        <EntityAnimation tag="Will" name="Idle" />
</cutscene>
```

#### LabelWrite

Changes what is written in a label

tag --> The tag of the Label that will target. (String)\
text --> The text that will appear (float)
time --> Marks the duration of this instruction. (float)

```XML
<cutscene>
    <LabelWrite tag="Main_lbl" text="Have you found it?" time="1.8f" />
</cutscene>
```

#### Parallel

This is a special Instruction, this instruction wraps other instructions. All the instructions inside a Parallel will be played simultaneously. The Parallel instruction will use the highest time at its own time.

```XML
<cutscene>
    <Parallel>
        <CameraDisplacement speedX="0.0" speedY="360.0" time="1.3f" />
        <EntityMove tag="Will" speedX="0" speedY="160" time="1.35f" />
        <EntityMove tag="Emily" speedX="0" speedY="300" time="1.3f" />
    </Parallel>
</cutscene>
```


## TODO

### TODO 1

Create a new script and add a way to load play it in `TestScene.cpp`.

**NOTE:** The engine has already the direction to the cutscene folder. All new scripts must be created there.

### TODO 2

Add at least one Entity, one label and one image to the script.

### TODO 3

Make the Entity you created be targeted by the camera, then make the entity move around the scene.

### TODO 4

In `CamInstruction.h` create a new sub instruction that only moves the camera to an entity's position but doesn't follow it along.

### TODO 5

Add the new instruction to the corresponding enum and map a string with this instruction.

**NOTE: The enum is located in `CutsceneContainer.h`.

### TODO 6

Make the `CutsceneContainer.cpp` able to generated and save this new instruction.
