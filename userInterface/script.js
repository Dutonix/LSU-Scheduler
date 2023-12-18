// User is required to fill two fields (department & semester) first before
// selecting other additional fields in narrowing their search
function requiredFields() {
  var department = document.getElementById('department').value;
  var semester = document.getElementById('semester').value;

  if (department.trim() !== ''  && semester.trim() !== '') {
      $('.additionalFields').css('display', 'inline');
  }
}

// selectize.js library
// used to customize the appearance of selecting information
$('#department').selectize();
$('#semester').selectize();
$('#courseNumber').selectize();
$('#preferences').selectize({ sortField: 'text' });

