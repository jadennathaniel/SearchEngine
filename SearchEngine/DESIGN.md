## High-level Design of Solution

- UML class diagram, etc.
- High-level pseudo code for each component.

## Your Timeline to Finish the Project
Weekly milestones/tasks. Set out a plan at the beginning and then record when you got it done.

|Task                       | Planned Completion | Actual Completion | Time spent in hrs by Jaden | Time spent in hrs by Benji |
|-------------------------- |--------------------|-------------------|----------------------------|----------------------------|
|AVL Tree + tests           | Nov 6              | Nov 8             |  4                         |  1                          |
|Map data structure         | Nov 6              | Nov 10            |  2                         |  2                          |
|Document Parser            | Nov 13             | Nov 12            |  3                         |  0                          |
|Indices                    | Nov 13             | Nov 15            |  2                         |  0                          |
|Query Processor + tests    | Nov 21             | Dec 3             |  8                         |  3                          |
|User interface             | Nov 24             | Dec 4             |  5                         |  2                          |
|Pesistence to index        | Nov 28             | Nov 17            |  3                         |  3                          |

## Used Data Structures
- AVLTree: We used trees to store the unique words from each article and each stop word. Trees have an average time complexity for O(logN) for searching and insertion. This is because with a binary search tree, during insertion and searching we are basically able to half the size of the tree during each traversal. Since we are inserting and searchng for every unqiue word found in a large dataset, a tree is better compared to a list. We also could have used a vector because insertion for a vector is O(1) but searching is O(n)

- unordered_map: We used unordered_map or hash map to store the documents and number of times a word was used in that document. The document was the key value and the number of times was the value. A hash map has an average time complexity of O(1) for insertion and searching. Since we wanted to find the number of time a word was found in each document when querying through the tree, the hashmap would have provided the fastest way to do so. We also could have used an AvlTree because of its relatively fast searching and inserting times. 

- vector: We wanted to sort the documents found according the highest relvancy ranking. We pushed the document to a vector using emplace_back, which has a time complexity of O(1). Afterwards we used std::sort to sort the vector which has a time complexity of O(n log n). We also could have used a tree to store the found documents because they have similar time complexities of O(log n).

## User Documentation 
- How to use the software.
<ol>
<li>Press run</li>
<li>Menu will display options</li>
<li> Enter 1 to create index from documents  <br>
    Enter 2 to write the index to a file  <br>
    Enter 3 to read an index from a file  <br>
    Enter 4 to enter a query  <br>
    Enter 5 to output statistics  <br>
    Enter 0 to exit  <br>
</li>
<li>If 1 is entered, type in the path of the folder that contains the documents that you want to index 
</ol>

Some example queries with the results.

Enter query: money

1

Title: METALS-Copper holds ground amid persistent dollar weakness
UUID: 7139dc7d642eec0467b6429abe94fb53ffc33e53
Author: 
Published: 2018-01-23T07:52:00.000+02:00

2

Title: EU sets bad example on human rights with NGO crackdown: U.N. expert
UUID: 00ad7f9008cae35eadd309508b95a1e78e940a8f
Author: Reuters Editorial
Published: 2018-01-27T01:43:00.000+02:00

3

Title: The money lesson LeBron James' uncles taught him when he was a kid
UUID: 25a1fad11497fec79711f7eee7534f775481df84
Author: Kathleen Elkins
Published: 2018-01-29T16:58:00.000+02:00

4

Title: LIVE MARKETS-Conglomerates? It's a kind of magic, M&A banker reckons
UUID: f602c2691ae0e8641ddb1ead9aaad0af2f53da7e
Author: 
Published: 2018-01-17T18:41:00.000+02:00

5

Title: Dell considering strategic options including IPO: CNBC, citing DJ
UUID: c514d6ec0ea27f79115131cd9472d214f9421ed2
Author: 
Published: 2018-01-26T04:49:00.000+02:00

6

Title: Bill Gates promised to pay off this country's $76 million debt — now he's doing it
UUID: ecdbe18d40340382712861004714a5fa1333bd96
Author: 
Published: 2018-01-18T21:42:00.000+02:00

7

Title: Commentary: How Apple Avoided Paying $40 Billion in Taxes | Fortune
UUID: e5fef609b2dd7e2962c9d39397323cf75c58ac35
Author: Josh Hoxie
Published: 2018-01-18T02:00:00.000+02:00

8

Title: China unlikely to raise rates, says ex-central banker
UUID: 8be77b8613b4b6a57d5a72bf222363ee205b05c5
Author: 
Published: 2018-01-23T18:37:00.000+02:00

9

Title: UPDATE 4-Lula's Brazil presidential run in doubt after conviction upheld
UUID: cd17ade61d226b29087c825021ca06ce2669c5d8
Author: 
Published: 2018-01-24T23:00:00.000+02:00

10

Title: Europe’s current ‘consensus’ trade could prove to be short lived, asset managers predict
UUID: c9eec9cb5741c4b7f8d8c4d4467a22d73046659d
Author: Silvia Amaro
Published: 2018-01-29T16:16:00.000+02:00

11

Title: ADM has made takeover approach to Bunge - WSJ
UUID: e84b27c6406839b7b8ebaac8aef0d3c6c083c520
Author: 
Published: 2018-01-19T23:59:00.000+02:00

12

Title: Do-good meat: are investors only after their pound of flesh?
UUID: 87cc72c65f65bc393e094bf846525c41a8ad8cda
Author: 
Published: 2018-01-26T12:00:00.000+02:00

13

Title: China raises 63-day reverse repo rate by 5 bps to 2.95 pct
UUID: 8faa9dd2ad09d32cce71da7ae652c629bbd84c12
Author: Reuters Editorial
Published: 2018-01-16T09:55:00.000+02:00

14

Title: LIVE MARKETS-Fuel price surge spells turbulence for airlines
UUID: 9947a4561abfc531ac73af57335ed5428121e8e7
Author: Reuters Editorial
Published: 2018-01-22T20:26:00.000+02:00

15

Title: Key senators want 'troublesome' intelligence measure out of spending bill
UUID: 7340a5c6b10f9f45df34d4a94dcf3b75bef4beb7
Author: Reuters Editorial
Published: 2018-01-23T04:34:00.000+02:00

Enter the document number you want to view. Enter to 0 to return to menu

1

>Text: January 23, 2018 / 5:56 AM / Updated 27 minutes ago METALS-Shanghai copper edges up amid persistent dollar weakness Reuters Staff 5 Min Read (Recasts to lead with ShFE copper, updates prices) BEIJING, Jan 23 (Reuters) - Shanghai copper prices gained ground on Tuesday amid a persistent weak dollar, even as official data showed China churned out a record volume of refined copper in December, suggesting the world's biggest copper consumer is well supplied. A weak dollar makes metals cheaper for holders of other currencies and supports prices, and the greenback's dive as a result of the U.S. government shutdown had seen copper climb by 0.4 percent in both Shanghai and London on Monday. "We think the recent copper price rebound is mostly driven by dollar weakness," Argonaut Securities wrote in a note. "Any dollar weakness reversal may weigh down on copper prices, in our view." While China's refined copper output hit an all-time high in December, Argonaut noted that unwrought copper imports fell by 5 percent in 2017. "The reduced import appetite reflects China's sluggish copper demand, especially in the power sector," it added. FUNDAMENTALS * SHFE COPPER: The most-traded March copper contract on the Shanghai Futures Exchange (ShFE) closed up 0.2 percent at 53,720 yuan ($8,395.06) a tonne. * LME COPPER: Three-month copper on the London Metal Exchange was down 0.3 percent at $7,044 a tonne, as of 0825 GMT, after rising as much as 0.4 percent earlier in the session. * NICKEL/LEAD: ShFE nickel and lead came alive after the mid-session interval, with nickel clocking a 1.7 percent rise to 99,720 yuan a tonne at the close, and lead gaining 1.9 percent amid tight stocks to end at 19,800 yuan a tonne, its highest close since Oct. 18. * NICKEL: SHFE nickel "drifted in line with onshore weakness, but unlike iron ore it did find some regional physical demand into the morning sell-off, the uptrend remains in tact for now," Marex Spectron wrote in a note. * USD: The dollar index inched up 0.1 percent, with the currency remaining near three-year lows after a rally following the deal to re-open the U.S. government. * CHINA: China's refined copper output jumped by 16.7 percent year-on-year to a record high in December, as smelters looked to churn out as much metal as possible ahead of a fall in treatment charges for copper concentrate. * SCRAP: China's imports of scrap copper fell 19.8 percent in December from a year earlier, customs data showed on Tuesday, as the country continues a clampdown on taking foreign waste. * ALUMINIUM: China's central Henan province churned out more aluminium than neighbouring Shandong in 2017 for the first time in years, becoming the nation's top-producing region. * MONGOLIA: Global miner Rio Tinto, will set up a new office in the Mongolian capital, separate from its giant Oyu Tolgoi project, to focus on exploration and local ties, strengthening its commitment to one of the world's greatest copper prospects. * CRYPTOCURRENCIES: Swiss-based commodities fund Tiberius Group plans to make a foray into cryptocurrencies with the launch of what may be the first digital money underpinned by physically deliverable metals including industrials such as aluminium and copper. * For the top stories in metals and other news, click or MARKETS NEWS * Asian stocks advanced on Tuesday after U.S. senators struck a deal to end a government shutdown in a boost to Wall Street, while the dollar turned higher against the yen after Bank Of Japan's chief reiterated his support for quantitative easing. PRICES BASE METALS PRICES 0757 GMT Three month LME copper 7068 Most active ShFE copper 53710 Three month LME aluminium 2235 Most active ShFE aluminium 14650 Three month LME zinc 3420 Most active ShFE zinc 26215 Three month LME lead 2619.5 Most active ShFE lead 19785 Three month LME nickel 12825 Most active ShFE nickel 99720 Three month LME tin 20715 Most active ShFE tin 146900 BASE METALS ARBITRAGE LME/SHFE COPPER LMESHFCUc3 972.56 LME/SHFE ALUMINIUM LMESHFALc3 -1957.58 LME/SHFE ZINC LMESHFZNc3 314.87 LME/SHFE LEAD LMESHFPBc3 -496.51 LME/SHFE NICKEL LMESHFNIc3 1472.79 ($1 = 6.3990 Chinese yuan) (Reporting by Tom Daly, Editing by Gopakumar Warrier and Sherry Jacob-Phillips)

## Performance
- Statistics for indexing all documents and timing.

Statistics:

- Time taken to index: 10776064 microseconds

- Total Number of Unique words: 40121

- Total Number of Documents: 1001

- Total Number of People: 1651

- Total Number of Orgs: 1831


## Automatic Tests and Memory Tests
You need to describe test cases for:
- Tests for your AVL tree's function
    - 
- Tests for your AVL tree for memory leaks (don't forget to test the persistence functions)
    - Ran valgrind on the whole program and valgrind showed zero memory leaks.
    -   ==4843== 

        ==4843== HEAP SUMMARY:

        ==4843==     in use at exit: 0 bytes in 0 blocks

        ==4843==   total heap usage: 1,822,012 allocs, 1,822,012 frees, 9,022,211,183 bytes allocated

        ==4843== 

        ==4843== All heap blocks were freed -- no leaks are possible

        ==4843== 

        ==4843== For lists of detected and suppressed errors, rerun with: -s

        ==4843== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0) 
- Tests for your index

- Tests for the complete system


## UML Class Diagram
<img src="UML class.jpeg">
