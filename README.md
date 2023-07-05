<h1>Minishell</h1>

<p>The aim of the Minishell project is to write a simple UNIX-like shell program in C. It's a great opportunity to learn about process handling, low-level programming, and file descriptor manipulation.</p>

<h2>Table of Contents</h2>

<ol>
  <li><a href="#about">About</a></li>
  <li><a href="#installation">Installation</a></li>
  <li><a href="#usage">Usage</a></li>
  <li><a href="#features">Features</a></li>
  <li><a href="#built-in-commands">Built-in commands</a></li>
</ol>

<h2 id="about">About</h2>

<p>Minishell is a challenge to create a working shell, similar to something like bash. The shell will have features like executing commands with their parameters, handling environment variables, and implementing some built-in commands.</p>

<h2 id="installation">Installation</h2>

<ol>
  <li>Clone the repository: <pre><code>git clone https://github.com/lpincoli/Minishell42.git</code></pre></li>
  <li>Move to the project's directory: <pre><code>cd Minishell42</code></pre></li>
  <li>Compile the project: <pre><code>make</code></pre></li>
</ol>

<h2 id="usage">Usage</h2>

<p>The shell should be launched from the command line after running 'make'. You should see a prompt displaying where you can enter various commands.</p>
<pre><code>./minishell</code></pre>

<h3 id="features">Features</h3>
<ul>
    <li>Display a prompt for new commands</li>
    <li>Command history</li>
    <li>Search and launch executables based on PATH variable or absolute/relative path</li>
    <li>Handle quotes and special characters</li>
    <li>Implement simple redirections and pipes</li>
    <li>Manage environment variables</li>
    <li>Handle ctrl-C, ctrl-D, and ctrl-\ inputs as bash does</li>
</ul>

<h3 id="built-in-commands">Built-in commands:</h3>
<ul>
    <li>echo with option -n</li>
    <li>cd with only a relative or absolute path</li>
    <li>pwd with no options</li>
    <li>export with no options</li>
    <li>unset with no options</li>
    <li>env with no options or arguments</li>
    <li>exit with no options</li>
</ul>

<h2>Subject</h2>

<p>For more information about the project, read the subject file.</p>
