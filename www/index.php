<!-- This is the project specific website template -->
<!-- It can be changed as liked or replaced by other content -->

<?php
  $domain=ereg_replace('[^\.]*\.(.*)$','\1',$_SERVER['HTTP_HOST']);
  $group_name=ereg_replace('([^\.]*)\..*$','\1',$_SERVER['HTTP_HOST']);
  $themeroot='http://r-forge.r-project.org/themes/rforge/';
  echo '<?xml version="1.0" encoding="UTF-8"?>';
?>

<!DOCTYPE html 
  PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" 
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
  <head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
    <title><?php echo $group_name; ?></title>
    <link href="<?php echo $themeroot; ?>styles/estilo1.css" rel="stylesheet" type="text/css" />
  </head>
  <body>
    <!-- R-Forge Logo -->
    <table border="0" width="100%" cellspacing="0" cellpadding="0">
      <tr>
        <td>
          <a href="/">
            <img src="<?php echo $themeroot; ?>/images/logo.png" border="0" alt="R-Forge Logo" /> 
          </a> 
        </td>
      </tr>
    </table>

    <!-- get project title  -->
    <!-- own website starts here, the following may be changed as you like -->

    <?php if ($handle=fopen('http://'.$domain.'/export/projtitl.php?group_name='.$group_name,'r')){
      $contents = '';
      while (!feof($handle)) {
        $contents .= fread($handle, 8192);
      }
      fclose($handle);
      echo $contents; } 
    ?>

    <!-- end of project description -->
    <h3>lhs package on CRAN</h3>
    <ul>
      <li><a href="http://cran.cnr.berkeley.edu/web/packages/lhs/index.html">Berkeley Mirror</a></li>
      <li><a href="http://lib.stat.cmu.edu/R/CRAN/web/packages/lhs/index.html">Statlib, Carnegie Mellon Mirror</a></li>
    </ul>
	
	<h3>lhs package vignettes</h3>
	<p>All package vignettes are created using RMarkdown and knitr</p>
	<ul>
	  <li><a href="lhs_basics.html">LHS Basic Operations</a></li>
	  <li><a href="augmentLHS_Example.html">Augmenting a LHS</a></li>
	</ul>

    <h3>R-Help Examples of using the LHS package</h3>
    <ul>
      <li><a href="http://article.gmane.org/gmane.comp.lang.r.general/77642">Latin hyper cube sampling from expand.grid()</a></li>
      <li><a href="http://article.gmane.org/gmane.comp.lang.r.general/231062">Latin Hypercube Sampling with a condition</a></li>
      <li><a href="http://article.gmane.org/gmane.comp.lang.r.general/132615">Latin Hypercube with condition sum = 1</a></li>
      <li><a href="http://article.gmane.org/gmane.comp.lang.r.general/287278">Latin hypercube sampling</a></li>
      <li><a href="http://article.gmane.org/gmane.comp.lang.r.general/300684">Latin Hypercube Sample and transformation to uniformly distributed integers or classes</a></li>
    </ul>  

    <h3>lhs package announcement</h3>
    <ul>
      <li><a href="http://article.gmane.org/gmane.comp.lang.r.general/65701">[R-pkgs] New R-Packages: Triangle and LHS</a></li>
    </ul>

    <h3>R-Forge Project Summary Page</h3>
    <ul>
      <li>You can find the project summary page <a href="http://<?php echo $domain; ?>/projects/<?php echo $group_name; ?>/"><strong>here</strong></a>. </li>
    </ul>

    <h3>Connections</h3>
    <ul>
      <li>You can find the C++ lhs project on <a href="https://github.com/">github</a> <a href="https://github.com/bertcarnell/lhs">here</a></li>
      <li><a href="http://www.rcpp.org/">Rcpp</a> is used in the project</li>
    </ul>

  </body>
</html>
