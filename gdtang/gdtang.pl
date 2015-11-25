#!/usr/bin/perl
# $Id: gdtang.pl,v 1.3 2005/03/17 13:50:35 yash Exp $
#
# GDTANG: Geographic Directed Tel Aviv University Network Generator
#
# Generate a scale-free directed with regard to geographic areas network 
# Arguments:
#   -n num_nodes [Default: 100]\n" .
#   -d avg_out_degree [Default: 2.11]\n" .
#   -i initial_size [Default: 5]\n" . 
#   -f file with country size info [Defaut gdtang-regions.txt (supplied)\n" . 
#   -a alpha value - probability of an edge to be local [Default: 0.5]\n" .
#   -p probability of adding double edges [Default: 0.07] \n" .
#
#
# Copyright (C) Avishai Wool and Sagy Bar , 2003-2005. All rights reserved.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# If you find this software useful, we ask that you cite our paper:
#
#    S. Bar, M. Gonen, and A. Wool.
#    A geographic directed preferential Internet topology model.
#    Technical report arXiv:cs.NI/0502061, 2005.
#    Available from http://arxiv.org/abs/cs.NI/0502061
#
# Send comments / requests / patches to:
#   Avishai Wool <yash@eng.tau.ac.il>
#   http://www.eng.tau.ac.il/~yash
#
#
# we start with a biconnected directed cycle of i nodes. in biggest country 
# then add n-i nodes, each with an average of d new edges.
#
# $Log: gdtang.pl,v $
# Revision 1.3  2005/03/17 13:50:35  yash
# *** empty log message ***
#
# Revision 1.2  2005/03/17 13:48:56  yash
# cleanup
#
#
# Revision 1.1  2004/11/23 00:00:10  SagyB
# Initial revision
#
#

use English;


use vars qw($opt_n $opt_d $opt_i $opt_h $opt_f $opt_a $opt_p);

my $vers_string = '$Revision: 1.3 $ ';
my ($vers) = $vers_string =~ /(\d+\.\d+)/;
my $USAGE      = "Usage: \n" .
                 "\t -n num_nodes [Default: 100]\n" .
                 "\t -d avg_out_degree [Default: 2.11]\n" .
                 "\t -i initial_size [Default: 5]\n" . 
                 "\t -f file with country size info [Defaut gdtang-regions.txt (supplied)\n" . 
		 "\t -a alpha value - probability of an edge to be local [Default: 0.5]\n" .
                 "\t -p probability of adding double edges [Default: 0.07] \n" .
                 "\t -h\t\t[This message]\n" .
                 "All arguments are optional.\n" ;

my $INVALID_FILE	="Invalid or empty file supplied. \n";
my $num_nodes = 100;
my $avg_degree = 2.11;
my $initial_size = 5;
my $alpha = 0.5;
my $INFTY = 999999999; 
my $Double_Edge_Prob=0.07;
my $seq_no;
my $base_countrygraph_name;
my $num_countries_to_print=4;

my $n_country_array;
my @country_distro;
my @country_array;

#Here we have such arrays for countries , meaning it will have country id once for each in/out endpoint in #this country . Real in/out_endpoint_marker arrays are attached to $country_array - an array for each country 


my $n_country_in_endpoint_marker;
my @country_in_endpoint_marker;

my $n_in_endpoint_marker;
my @in_endpoint_marker;

my $n_out_endpoint_marker;
my @out_endpoint_marker;

my $n_country_out_endpoint_marker;
my @country_out_endpoint_marker;


my @nodes;
my $total_out_degrees = 0; # this is n_edges
my $current_n_nodes = 0;

my ($low_edges_per_node, $high_edges_per_node);


use Getopt::Std;

my @save_argv = @ARGV;

my $script_path = `dirname $PROGRAM_NAME`;
my ($prog) = $PROGRAM_NAME =~ /([^\/]*)$/;
chomp $script_path;

if (! getopts('n:d:i:f:a:p:h'))
  {
    die $USAGE;
  }


if (defined $opt_h)
{
  print $USAGE;
  exit(0);
}

if ((defined $opt_p) and (($opt_p >= 0) and ($opt_p<=1)))
{
  $Double_Edge_Prob=$opt_p;
}

#define the country distribution file and read input
my $DEFAULT_REGION_FILE = "gdtang-regions.txt";
my $region_file = $opt_f;

if (! defined $opt_f)
{
    $region_file = "$script_path/$DEFAULT_REGION_FILE";
}
read_input();
#end of definition and reading of input file 


if ((defined $opt_n) and $opt_n > 0)
{
    $num_nodes = $opt_n;
}

if ((defined $opt_a) and (($opt_a >= 0) and ($opt_a<=1)))
{
    $alpha = $opt_a;
}

if ((defined $opt_d) and $opt_d >= 2)
{
    $avg_degree = $opt_d;
}
if ((defined $opt_i) and $opt_i >= 3)
{
    $initial_size = $opt_i;
}

my  $seq_no=1;





#
# avoid trivialities
#
if ($num_nodes < $initial_size)
{
    $num_nodes = $initial_size;
}

$low_edges_per_node = int($avg_degree);
$high_edges_per_node = $low_edges_per_node + 1;
if ($low_edges_per_node eq $avg_degree)
{
    $high_edges_per_node = $low_edges_per_node;
}

$#nodes = $num_nodes;   # create a big array
 



make_init();
add_random_edges();
print_output();
exit(0);





#-------------------------------------------------
#function name :read_input
#description   :read the country distro file - one integer from each line 
#		performed before initialisation of other parts of code
#input 	       :none, uses global variable #refion_file for file name, 
#		set to "gdtang-regions.txt" (supplied) by default
#output	       :indirect, produces @country array with stats perl each country 
#-------------------------------------------------


sub read_input
{
   open(MYFILE, $region_file) || die "Failed to open $region_file\n";
   $n_country_array=0;

#read the input from supplied input file .
   while (<MYFILE>)
    {
	next if (/^\#/); # skip comments
	($u) = $_ =~//;
	if (defined $u)
	  {
	    push @country_array , $u;
	    $sum+=$u;
	    $n_country_array++;
           
	  } 

    }
   close(MYFILE);

  

#recalculate the distro 
  for ($u=0; $u<$n_country_array; $u++)
    {
      $temp=$country_array[$u]/$sum;
      $country_array[$u]=$u;
      if ($u != 0)
	{

	  $country_array[$u]->{lower_bound}=$country_array[($u-1)]->{upper_bound};
	}
      else
	{
	  $country_array[$u]->{lower_bound}=0;
	}
      
      $country_array[$u]->{upper_bound}=$country_array[$u]->{lower_bound}+($temp);
      $country_array[$u]->{upper_bound}= 1 if ($u ==($n_country_array-1));
    }	

 
}      

#-------------------------------------------------
#function name : get_country_num
#description   : pick a country according to country distribution
#input 	       : random number [0..1] 
#output	       :  country number 
#-------------------------------------------------

sub get_country_num
{
  my ($u)=@_;
  my $i;
  print "u is $u \n";
  if (($u<0) or ($u>1))
   {
	printf("Impossible U value , should be 0..1 \n");
        exit(0);
   }
  if ($u==0)
   {
	return 0;
   }

  for ($i=0;$i<$n_country_array;$i++)
   {
     if (($u > $country_array[$i]->{lower_bound}) and ($u <= $country_array[$i]->{upper_bound}))
        {
	  return $i;
        }
   }
  return -1;
}


#-------------------------------------------------
#function name : make_init
#description   : create an initial biconnected directed cycle
#input 	       : none
#output	       :indirect, updated @nodes array
#-------------------------------------------------

sub make_init
{
    my $u;
    my ($country_u,$country_v,$first_country);
    for ($u = 1; $u < $initial_size; $u++)
    {
			$country_u=choose_country();
      $first_country=$country_u if ($u eq 1 );
			$country_v=choose_country();
			add_edge($u,$country_u, $u+1,$country_v);
			add_edge($u+1,$country_v, $u,$country_u); # //First Bug 
    }
    add_edge(1, $first_country,$initial_size,$country_v);
    add_edge($initial_size, $country_v,1,$first_country);
    $current_n_nodes = $initial_size;
}




#-------------------------------------------------
#function name : add_edge
#description   : insert an edge between u and v
#input 	       : 1st vertex#, country to which 1st vertex belongs , 2nd vertex, country to which
#              : the 2nd vertex belongs
#output	       : adds vertex#1 and vertex#2 to @nodes (if they weren't defined before)
#	         adds vertex #2 to vertex #1 out neighbours and vertex #1 to vertex#2 in neighbours
#                also updated by country arrays for both countries in the same way
#-------------------------------------------------



sub add_edge
{
    my ($u,$u_country, $v,$v_country) = @_;
    my ($du, $dv, $extra_markers_u, $extra_markers_v);
    my $i;

    if ($u <= 0 or $v <= 0 or ! defined $v or ! defined $u)
    {
			die "adding edge but bad vertices given $u $v \n";
    }

    $du = $nodes[$u]->{out_degree};
#the extra_markers variable if for future use, currently set to 1 
    $extra_markers_u = 1; ### utility($du+1) - utility($du);
   
    $nodes[$u]->{out_degree}++;
    $nodes[$u]->{out_neighbors}{$v} = 1;
    $nodes[$u]->{country}=$u_country; 
    $dv = $nodes[$v]->{in_degree};
    $extra_markers_v = 1; ### utility($dv+1) - utility($dv);
    $nodes[$v]->{in_degree}++;
    $nodes[$v]->{in_neighbors}{$u} = 1;
    $nodes[$v]->{country}=$v_country;
  
#if they are both in the same country, then it's an inter-country edge 
#and hence it's updated in respective country's array  
    if ($u_country eq $v_country)
    {
    	
    	if (! defined $country_array[$u_country]->{nodes}[$u]->{neighbours}{$v} )
    		{
    			$country_array[$u_country]->{num_in_edges}++ ;
    			$country_array[$u_country]->{nodes}[$u]->{neighbours}{$v}=1;
    			$country_array[$u_country]->{nodes}[$u]->{degree}++;
    			$country_array[$u_country]->{nodes}[$u]->{alive}=1;
    		}
    	if (! defined $country_array[$v_country]->{nodes}[$v]->{neighbours}{$u} )
    		{	
    			$country_array[$v_country]->{nodes}[$v]->{neighbours}{$u}=1;
    			$country_array[$v_country]->{nodes}[$v]->{degree}++;
    			$country_array[$v_country]->{nodes}[$v]->{alive}=1;
    		}
    }	
   
   	

   push @in_endpoint_marker,$v;
   $n_in_endpoint_marker++;
   push @out_endpoint_marker,$u;
   $n_out_endpoint_marker++;
   

   print STDERR "Adding $u->$v ($extra_markers_u, $extra_markers_v)\n" 
	 if $debug > 30;


    for ($i = 0; $i < $extra_markers_u; $i++)
    {
			push @{$country_array[$u_country]->{out_endpoint_marker}}, $u;
			$country_array[$u_country]->{n_out_endpoint_marker}++;
    }

    for ($i = 0; $i < $extra_markers_v; $i++)
    {
			push @{$country_array[$v_country]->{in_endpoint_marker}}, $v;
			$country_array[$v_country]->{n_in_endpoint_marker}++;
    }
    
    
    $total_out_degrees ++;
    $current_n_edges ++;
}

#-------------------------------------------------
#function name : do_rand
#description   : self explanatory
#input 	       : an integer
#output	       : random number [1..input]
#-------------------------------------------------
#---------------------------------------
# return a random integer in thge range {1,..,u}, including endpoints
sub do_rand
{
    my ($u) = @_;

    return int(rand($u)) + 1;

}



#-------------------------------------------------
#function name : choose_country
#description   : choose country according to country distro - used for adding new vertices
#input 	       : none
#output	       : country number 
#-------------------------------------------------
#----------------------------------------------
# choose country according to country distro
sub choose_country
{
   my $random_0_1 = rand(1);
   my $i=0;
   return (0) if ($random_0_1==0);
   for ($i=0;$i<$n_country_array;$i++)
    {
      if (($random_0_1 > $country_array[$i]->{lower_bound}) and 
		($random_0_1 <= $country_array[$i]->{upper_bound}))
	 	   {
			return $i;
		   }
    }
   print "country not found !!! \n";
 #  exit (0);
return -1;
}

#-------------------------------------------------
#function name : add_random_edges
#description   : add directed edges at random as described in Directed Geo model
#input 	       : none
#output	       : generated directed graph 
#-------------------------------------------------


sub add_random_edges
{
    my $u;
    my $edge_index;
    my $temp_avg_degree;

    for ($u = $initial_size + 1; $u <= $num_nodes; $u++)
    {
			print STDERR "." if (($u % 100) eq 0) ;
			$current_n_nodes++;
			for ($edge_index=0; $edge_index < $low_edges_per_node; $edge_index++)
				{
	    			new_preferential_edge($edge_index, $u);
				}

# check if we can add another edge (outdegree grows by 1)
		$temp_avg_degree = ($total_out_degrees + 1) / $current_n_nodes;
		if ($temp_avg_degree <= $avg_degree)
			{
	    	new_preferential_edge($edge_index, $u);
			}
    }
}


  
  
#-------------------------------------------------
#function name : 
#description   :
#input 	       :
#output	       :
#-------------------------------------------------         

#-------------------------------------------------
#function name :new_preferential_edge
#description   : add a edge number edge_index during the round in which the new node u
# 		 is added. The new edge is not necessarily connected to u:
#  		 if edge_index == 0 then u is the 1st endpoint
#  		 otherwise:
#    		 pick the 1st endpoint preferentially by in-degree
#  		 the 2nd endpoint is chosen perferentially by out-degree
#  		 if we fail to find a new 2nd endpoint, we force the 1st endpoint to be u
#  		 and try again. 
#input 	       : none
#output	       : inderect - previous graph with new edge added
#-------------------------------------------------
#---------------------------------------
# 
# 
sub new_preferential_edge
{
    
	
    my ($edge_index, $u) = @_;
		my ($x, $v , $country,$random_0_1);
    $country=-1;
    if ($edge_index eq 0)
    { 
    	# always add one edge to $u
	$x = $u;
        $country=choose_country();
    }
# the next edges go to randomly chosen nodes
    else 
    {
		$random_0_1 = rand(1);
#as described in model definition 
      		if ($random_0_1<=$alpha)
				{
				   $country=choose_country();					
				}
		$x = do_preferential(-1, 'in',$country); 
     }
#print LogFile "finished choosing In vertex , got $x \n";
# x can be any node, no need to chek
# if it's already someone's neighbor
#print LogFile "choosing OutVertex from Global List \n";
    $v = do_preferential($x, 'out',$country); 
	    
    if ($v < 0)
    {
# we failed because x already has many neighbors
# so switch back to $u, the new node we created, and give it
# another edge. this introduces a small bias in the 
# distribution
			$x = $u;
#so it will be added with u's original country
#$edge_index=0;
      $country=choose_country() if ($country eq -1);
			$v = do_preferential($x, 'out',$country); 
	
			if ($v < 0)
			{
	    	die 
				"failed to find a neighbor for node $u ?\n";
			}
    }
    $random_0_1 = rand(1);
    
    
    if ($edge_index != 0)
    {
        add_edge($x,$nodes[$x]->{country},$v,$nodes[$v]->{country});
#handle the issue of double edges - make edge double with probability p
        if ($random_0_1<$Double_Edge_Prob)
          {
            add_edge($v,$nodes[$v]->{country},$x,$nodes[$x]->{country})
          }	
    }
    else 
    {
        add_edge($x,$country,$v,$nodes[$v]->{country});
#handle the issue of double edges - make edge double with probability p
  	if ($random_0_1<$Double_Edge_Prob)
          {
            add_edge($v,$nodes[$v]->{country},$x,$country);
          }
    }
    
   close (LogFile); 
	
}


#-------------------------------------------------
#function name : do_preferential
#description   : pick a node preferentially at random to be a neighbor of u
# 		 if type = 'in' use in-degree distribution, otherwise use out-degree
#input 	       : source country number, type, country code (-1) for global edges
#output	       : returns the vetex to be connected to input vertex
#		 returns -1 if we fail to find a new possible neighbor.
#-------------------------------------------------   


sub do_preferential
{
    #country_code will be set to -1 for global edjes 
    my ($u, $type,$country_code) = @_;
    my ($v, $rand_index,$edge_);
    my $trys = 0;

    my ( $random_0_1);

    $v = -1;
    while (1)
    {
		  $trys++;
			if ($type eq 'in')
			{
#If it's the case in which the country was provided , choose preferentially 
#from this country's in_endpoint_marker_array . If not , choose the country
#preferentially by total in_degree distro and then choose edge .
#The problem with it is that the previously chosen country might not have any nodes in it
#in this case , we choose it from suitible by country preferential list
				 if (($country_code eq -1) or 
		 	 		(! defined $country_array[$country_code]->{n_in_endpoint_marker}))
						{
         			$rand_index=do_rand($n_in_endpoint_marker);
 		  	 			$rand_index--;
		  	 			$v=$in_endpoint_marker[$rand_index];
      			}
    		else 
      			{
        			$rand_index = do_rand($country_array[$country_code]->{n_in_endpoint_marker});
		    			$rand_index--; # do_rand returns values 1-max, need 0-max-1 
     					$v = $country_array[$country_code]->{in_endpoint_marker}[$rand_index];
      			}          
	        
			}

		else
		{
#Same idea as previously 
	   		if (($country_code eq -1) or 
			 		(! defined $country_array[$country_code]->{n_out_endpoint_marker}))
			 			{
         			$rand_index=do_rand($n_out_endpoint_marker);
 		   	 			$rand_index--;
		  	 			$v=$out_endpoint_marker[$rand_index]; 
       			}
     		else
      			{
          		$rand_index = do_rand($country_array[$country_code]->{n_out_endpoint_marker});
		      		$rand_index--; # do_rand returns values 1-max, need 0-max-1
		      		$v = $country_array[$country_code]->{out_endpoint_marker}[$rand_index];
		  			}
		
		}

	 if ($v != $u) 
		{
			if  ($type eq 'out')
		     {
		     	 last if ($nodes[$u]->{out_neighbors}{$v} != 1)
				 }
	  	if  ($type eq 'in')
		     {
		     	 last if ($nodes[$u]->{in_neighbors}{$v} != 1)
		     }
		}

# sometimes, usually early on in the generation process, a node u
# already has so many neighbors that we can't connect a new edge to it.
# so we give up and return -1
	if ($trys > 2*$high_edges_per_node)
	{
	    $v = -1;
	    last;
	}
       
    }
    return $v;
}







#-------------------------------------------------
#function name : numeric
#description   : self explanatory
#input 	       :
#output	       :
#-------------------------------------------------
sub numeric
{
    $a <=> $b;
}



#-------------------------------------------------
#function name : print_output
#description   : prints the output
#input 	       : none
#output	       : none
#-------------------------------------------------
	 

sub print_output
{
    my ($u, $v);
    print "#\n";
    print "# $prog: A geographic directed scale-free graph generator $vers\n";
    print "# Copyright (c) 2003-2005, Avishai Wool and Sagi Bar\n";
    printf "# command line: %s %s\n", $prog, join " ", @save_argv;
    print "# Generated on ", `date`;
    print "# num_nodes=$num_nodes\n";
    print "# num_edges=$current_n_edges\n";
    print "# avg_degree=$avg_degree\n";
    print "# alpha=$alpha\n";
    print "# probability for double edge=$Double_Edge_Prob \n";
    print "# initial_size=$initial_size\n";
    print "# country distribution file name=$region_file \n";
    for ($u = 1; $u <= $num_nodes; $u++)
    {
	foreach $v (sort numeric keys %{$nodes[$u]->{out_neighbors}})
	{
	    $num_edges++;
	    print "$u $v\n";
	}
    }

}
