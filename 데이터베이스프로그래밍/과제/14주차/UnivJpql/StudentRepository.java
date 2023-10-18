package dbp.UnivJpql.repository;

import dbp.UnivJpql.entity.Student; // Student.java 경로
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Modifying;
import org.springframework.data.jpa.repository.Query;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.Optional;

public interface StudentRepository extends JpaRepository<Student, Long> {
    @Query(value = "from Student where id = ?1") // id로 검색
    public Optional<Student> findStudentById(Long id);
}




