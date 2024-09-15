Hello,

did Test B, using the First Person Template.
Instead of just creating one skill, I tried to focus more on the systemic side of things.
At first I wanted to use GAS for it as I am a big  fan of it, but I instead switched to a custom solution for making it more straightforward.

The controls are currently mapped to the NUM keys but can easily be adjusted in the EI context of the skills.

The skill actor comp is attached to the player controller and used for setting up the data assets of the skills to use. It also manages the runtime instance of a skill.
Every skill is deriving from SkillBase.
