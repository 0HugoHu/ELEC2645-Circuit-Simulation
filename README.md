# ELEC2645-Circuit-Simulation
Circuit simulator for validation of huffman coding, sending and receiving waves. 

# Coursework Requirements
By the end of this unit, student should be able to:
- Design and develop a large software project Write, compile, run and de-bug complex C++ programs using appropriate software engineering techniques.
- Demonstrate initiative, independent learning, creativity, problem-solving, time management and project management skills.
- Present their work in an effective manner.

# Introduction

In this project, we want to convert the user input text to binary Huffman code, next to sinewave (to simulate its propagation in air), then to superimposed noise (to simulate the interference during signal transmission), and finally to a filtered decoding circuit that the received wave in the form of a tiny current. The user is free to modify the parameters and properties of different components in the circuit (even the intensity of the superimposed noise) to see how the signal will be output at different locations in the circuit. Ultimately, after the filter circuit and comparator, the non-regular sinusoidal current signal is converted into a regular square wave signal, which is then binary coded. The program uses a Huffman decoding algorithm to restore the binary code to text.

As newcomers to this field, this program will help them understand what Huffman coding and decoding is, how noise can interfere with a signal, what level of noise can be filtered, and how to modify the properties of circuit components to get better filtering results.

The project runs on the Windows command line, but we expect to end up with colorful circuit diagrams and sinusoidal and square wave diagrams. A graphical interface is always more helpful for users to understand what they are doing.


# Preview
|  |  |
|--|--|
|![](https://s1.ax1x.com/2022/07/22/jOcMef.png)|![](https://s1.ax1x.com/2022/07/22/jOc3Fg.png)|
![](https://s1.ax1x.com/2022/07/22/jOcuOP.png)|![](https://s1.ax1x.com/2022/07/22/jOcQw8.png)|
![](https://s1.ax1x.com/2022/07/22/jOclTS.png)|![](https://s1.ax1x.com/2022/07/22/jOc8YQ.png)|
![](https://s1.ax1x.com/2022/07/22/jOcNyq.png)|![](https://s1.ax1x.com/2022/07/22/jOctln.png)|
![](https://s1.ax1x.com/2022/07/22/jOcGWj.png)|![](https://s1.ax1x.com/2022/07/22/jOcYSs.png)|

# Key Features
1.  Huffman encoding and decoding process illustration, with Huffman binary tree shows the binary codes of each character, and the figures of emitting sine wave and receiving square wave superimposed on noise.
2.  Demonstrate what the receiver circuit looks like, with colourful electronic components and instructions.
3.  Change the value and the colour of any component during run time.
4.  Save the circuit, so that when the console is closed and opened again, the circuit remembers previous changes.
5.  Partial circuit simulation implemented.

# Individual Final Version Presentation
**1. Main Menu (implemented by Yusen Liu)**

![](https://minerva.leeds.ac.uk/bbcswebdav/internal/courses/202021_34256_XJEL2645/wikis/group/7a59be190ca14294b520c281abd55b71/c41981f332f94ddabf3c0ee34f4e0e88/QQ%E6%88%AA%E5%9B%BE20201208232036.png)

This is the main menu of this program, use can enter 1-4 to choose the function they like.

But for a starter, he may first encode some texts. Let's move into the "1. Encode" function.

**2. Encode (algorithm implemented by me)**

![](https://minerva.leeds.ac.uk/bbcswebdav/internal/courses/202021_34256_XJEL2645/wikis/group/7a59be190ca14294b520c281abd55b71/c41981f332f94ddabf3c0ee34f4e0e88/QQ%E6%88%AA%E5%9B%BE20201208233248.png)

This is the encode interface, the algorithm is completed by me while the interface is created by Yusen Liu. There's a short sentence  and an example  explain what this function does. The user can press the number 0 to turn back to main menu.

Here, I want to encode this sentence: "I am handsome!".

As I pressed 'enter', we go to the next page.

**3. Encode Result (algorithm and figures implemented by me)**

![](https://minerva.leeds.ac.uk/bbcswebdav/internal/courses/202021_34256_XJEL2645/wikis/group/7a59be190ca14294b520c281abd55b71/c41981f332f94ddabf3c0ee34f4e0e88/QQ%E6%88%AA%E5%9B%BE20201208233644.png)

The left part shows the the compression ratio, the binary code and the Huffman tree leaves. Each leave represents one character's binary code. The right part shows the square wave of this binary code, and this square wave is transformed into a sine wave as shown below, which is the signal transferred in air.

Now, let's press 0 to go back to main menu, and press 2 to go to the "2. Circuit" function.

**4. Circuit  **(each component template, the way to connect component, setting the colour and position, the sub-menu and IVConverter circuit are implemented by me)****

**![](https://minerva.leeds.ac.uk/bbcswebdav/internal/courses/202021_34256_XJEL2645/wikis/group/7a59be190ca14294b520c281abd55b71/c41981f332f94ddabf3c0ee34f4e0e88/QQ%E6%88%AA%E5%9B%BE20201208234236.png)**

This is the whole filter and decoding circuit. This circuit contains three parts:

1. IVConverter (before the IVC Out as shown in circuit), to overlay the noise and original signal, and a amplifier to increase the input current to a large voltage.

2. Comparator (before the Comp Out) to transfer the sine wave into a square wave.

3. ADC to transfer the continuous square wave into a sequence of bits, then display the decoding result.

Note that, for a input of "I am handsome!", the decoding result is  not correct, it's "nmmedaaaoa! ss". This is because the noise intensity is too high or the capacitance and resistance are not matching, that this circuit cannot correctly remove the noise. In this situation, the information carried by this signal is lost.

Actually we can press "3 - Analyse" to see what happened by seeing the output at each position of this circuit to analyse the specific problem, but this part is not completed by me.

Assume that the key problem is high noise intensity, so now let's change it.

By pressing "1 - Change value", here we choose "1 - Noise Source" and changed the value to "0.01". There is a hint said "Property changed succeeded!". After 3 seconds, the circuit is reloaded.

![](https://minerva.leeds.ac.uk/bbcswebdav/internal/courses/202021_34256_XJEL2645/wikis/group/7a59be190ca14294b520c281abd55b71/c41981f332f94ddabf3c0ee34f4e0e88/QQ%E6%88%AA%E5%9B%BE20201209100259.png)

Now we can see that the second screen  correctly  displayed our decoding value: "I am handsome!".

![](https://minerva.leeds.ac.uk/bbcswebdav/internal/courses/202021_34256_XJEL2645/wikis/group/7a59be190ca14294b520c281abd55b71/c41981f332f94ddabf3c0ee34f4e0e88/QQ%E6%88%AA%E5%9B%BE20201209100310.png)

This indicates the noise is completely removed by this circuit, and each binary bit is correct at this time.

By now, that's try to change the colour.

I think the original "BLUE" colour of the resistor Rf=5.5MΩ is not beautiful. Let's change it to a "GREEN" colour.

![](https://minerva.leeds.ac.uk/bbcswebdav/internal/courses/202021_34256_XJEL2645/wikis/group/7a59be190ca14294b520c281abd55b71/c41981f332f94ddabf3c0ee34f4e0e88/QQ%E6%88%AA%E5%9B%BE20201209100936.png)

![](https://minerva.leeds.ac.uk/bbcswebdav/internal/courses/202021_34256_XJEL2645/wikis/group/7a59be190ca14294b520c281abd55b71/c41981f332f94ddabf3c0ee34f4e0e88/QQ%E6%88%AA%E5%9B%BE20201209100941.png)

Even I closed the console now and restart again, the resistor still remains its "GREEN" colour, since all of the properties are stored in files.

You may have noticed that, we can only change a few properties here, that's because only I did the implementation of changing values, since only my IVConverter part's components can be changed.

Besides, if you input a wrong number here, there's also a hint:

![](https://minerva.leeds.ac.uk/bbcswebdav/internal/courses/202021_34256_XJEL2645/wikis/group/7a59be190ca14294b520c281abd55b71/c41981f332f94ddabf3c0ee34f4e0e88/QQ%E6%88%AA%E5%9B%BE20201209101343.png)

By pressing "0 - Back", we returned to the main menu. Now let's press "3 - Decode".

**5. Decode **(the algorithm is implemented by Keyi Zhou and me, the figure is implemented by me)****

****![](https://minerva.leeds.ac.uk/bbcswebdav/internal/courses/202021_34256_XJEL2645/wikis/group/7a59be190ca14294b520c281abd55b71/c41981f332f94ddabf3c0ee34f4e0e88/QQ%E6%88%AA%E5%9B%BE20201209101903.png)****

After we changed the noise intensity, we have known the decoding output is correct. In this decode page, we can clearly compare the original values and decoded values.

If the circuit failed to decoding, you may notice different square waves (the above indicates the original bits without noise added while the bottom means the bits with noise added after the filter circuit). They are absolutely the same in this situation, the noise have no influence on the signal.

If the decoded outcome is not correct, this program will even give you some suggestions on how to change the circuit. Let's leave this part to be illustrated in Group Wiki.

# I learned
At the algorithmic level, I had a deep understanding of the principles of Huffman encoding and how to apply it to encrypt and decode simple text. However, in the course of the experiment, I also found the shortcomings of Huffman: Huffman is very friendly to English text, because there are only 26 letters in total, and in any text, the letter repetition rate is very high and the compression rate since is very good. But for non-English text, such as Chinese characters or Japanese, each individual text cannot be disassembled, and the number of commonly used characters can be up to 5,000. The compressibility of Huffman coding will be greatly reduced. Also, from a review of the literature [1], Huffman encoding has a low compression ratio for images and is not suitable for transmitting signals for video streaming.

At the application level, I learned how to use the Windows API to control the display size of the current window application and to change the colour of text characters by modifying the command line display font. One of the most used functions in this project is the positioning of the command line cursor to a specific location, which I adapted by referring to the implementation of the drawing function. File reading and writing is key to the program's ability to interact with data from asynchronous processes (refers to different class in this project). I learned how to write a stream of data to a file by character, how to read a file by line, and how to implement changes to existing file with specified content. Of course, I also learned some small but shining functions, such as simulating animation effects using the Windows Sleep() function, which is a transfer from my previous knowledge base and I won't go into detail here.

In terms of course knowledge, I used a combination of menus, classes, string manipulation, loops, and pointers to write code that was in line with Google Code Style and C++ programming specifications. After this five-week project, I became more proficient and comfortable with these basic programming modules.

**For the application of the Software Engineer Guidelines:**

1. Have a solid foundation.
This is reflected in the fact that my code writing conforms to the Google Code Style required for the assignment, as well as the object-oriented programming guidelines of C++. Without a solid professional foundation (since I have a minor in software engineering), it would be difficult for me to use data structures such as vector, map, queue, etc. correctly, use pointers properly and avoid memory leaks.

2. Have a rich imagination.
For example, I couldn't display pictures, I couldn't draw, I could only use 4-bit colors, and I couldn't display many non-ASCII codes on the command line. However, I used my imagination to show the whole circuit diagram by filling in the background or using a combination of characters, and even realized the drawing of function figures.

3. Good project management.
As you can see from the individual wikis, since the first week of the team meeting, we have had a reasonable division of work and schedules to keep the project on track. Everyone, no matter how good or bad the foundation is, can learn something from the process of the project.

4. Help your teammates with integrity.
I often help my teammates in the development process, but I do not interfere too much with their work, but inspired them by guiding them step by step through their tasks. I listened carefully to my teammates' opinions, did not complain, and actively worked with them to improve the project.

**For teamwork**

Teamwork is challenging because we don't know the basics of what others know, and they may have a different perspective on key project decisions than we do. However, the value of the team's creativity far outweighs the risk of the challenge. I think we worked very well together as a team, but from my personal perspective, I would like to share my thoughts on this team project.

1. The team should have a team leader who is responsible for the overall development progress of the project (I held this position in this project). But more importantly, the team leader needs to know what the team members are good at and what they really like to do. There is an old Chinese saying: teach according to your ability - you can't ask a student who is good at algorithms but messed up in interface design to do some work with the interface - you can't ask a student who still lacks in knowledge base to try very deep and complex code. Moreover, the team leader needs to supervise the team members to complete the tasks on time.

2. The team needs to be full of encouragement. Sometimes you may think it's not surprising when someone finally does what they want after failing a thousand times, but for them, it's a big surprise, this is a great progress. If you can praise him at this moment, he will appreciate it, and this is the key to maintaining a good team atmosphere.

3. Have more team discussions instead of working on your own. Creative thinking is often sparked by the verbal exchange of ideas between team members. If you don't know what to do next, or if you've been thinking about a problem for a long time and don't have an agreed-upon way to implement it, it's a good idea to discuss it with your team members. The Jews always say that one plus one is greater than two. The pooling of everyone's thoughts can often lead to unexpected creativity.
